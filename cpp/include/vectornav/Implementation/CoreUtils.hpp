// The MIT License (MIT)
// 
// VectorNav SDK (v0.22.0)
// Copyright (c) 2024 VectorNav Technologies, LLC
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef VN_COREUTILS_HPP_
#define VN_COREUTILS_HPP_

#include <stdint.h>

#include <cstdio>
#include <cstring>

namespace VN
{

inline void _calculateCheckSum(uint8_t* checksum, uint8_t byte) noexcept { *checksum ^= byte; }

inline uint8_t CalculateCheckSum(uint8_t* buffer, uint64_t bufferSize) noexcept
{
    uint8_t checksum = 0;
    for (uint64_t i = 0; i < bufferSize; i++) { _calculateCheckSum(&checksum, buffer[i]); }
    return checksum;
}

inline void _calculateCRC(uint16_t* crc, uint8_t byte) noexcept
{
    *crc = static_cast<uint16_t>((*crc >> 8) | (*crc << 8));
    *crc ^= byte;
    *crc ^= ((*crc & 0xFF) >> 4);
    *crc ^= ((*crc << 8) << 4);
    *crc ^= (((*crc & 0xFF) << 4) << 1);
}

inline uint16_t CalculateCRC(uint8_t* buffer, size_t bufferSize) noexcept
{
    uint16_t crc = 0;
    for (size_t i = 0; i < bufferSize; i++) { _calculateCRC(&crc, buffer[i]); }
    return crc;
}

inline bool frameVnAsciiString(const char* inputHead, char* outputHead, [[maybe_unused]] const size_t outputCapacity)
{
    sprintf(outputHead, "$VN%s", inputHead);
    const uint16_t len = strlen(outputHead);
    uint16_t crcValue = CalculateCRC((uint8_t*)outputHead + 1, len - 1);
    sprintf(outputHead + len, "*%04X\r\n", crcValue);
    return false;
}

}  // namespace VN
#endif  // VN_COREUTILS_HPP_
