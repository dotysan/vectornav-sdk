// The MIT License (MIT)
// 
// VectorNav SDK (v0.99.0)
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

#ifndef VN_CLI_EXCEPTIONS_HPP_
#define VN_CLI_EXCEPTIONS_HPP_

#pragma managed(push, off)
#include "vectornav/Interface/Errors.hpp"
#pragma managed(pop)

using namespace System;

namespace VNSDK
{

public
ref class VnException : public Exception
{
public:
    VnException(VN::Error error) : Exception(gcnew String(VN::errorCodeToString(error)))
    {
    }
    VnException(VN::ErrorAll errors) : Exception(gcnew String(VN::errorCodeToString(errors)))
    {
    }
#if (PLUGIN_FIRMWAREPROGRAMMER)
    VnException(VN::FirmwareProgrammer::ErrorBL error) : Exception(gcnew String(VN::errorCodeToString(error)))
    {
    }
#endif
#if (PLUGIN_CALIBRATION)
    VnException(VN::Calibration::ErrorCal error) : Exception(gcnew String(VN::errorCodeToString(error)))
    {
    }
#endif
};

} // namespace VNSDK

#endif // VN_CLI_EXCEPTIONS_HPP_
