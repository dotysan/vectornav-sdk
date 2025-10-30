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

#ifndef VN_ERRORS_HPP_
#define VN_ERRORS_HPP_

#include <stdint.h>

#include <variant>

#include "vectornav/Config.hpp"
#include "vectornav/HAL/Timer.hpp"
#include "vectornav/TemplateLibrary/String.hpp"

#if __has_include("FirmwareProgrammer/include/vectornav/FirmwareProgrammerErrors.hpp")
#include "FirmwareProgrammer/include/vectornav/FirmwareProgrammerErrors.hpp"
#define _VN_ERROR_BL , FirmwareProgrammer::ErrorBL
#else
#define _VN_ERROR_BL
#endif

#if __has_include("Calibration/include/vectornav/CalError.hpp")
#include "Calibration/include/vectornav/CalError.hpp"
#define _VN_ERROR_CAL , Calibration::ErrorCal
#else
#define _VN_ERROR_CAL
#endif

#define _VN_ERROR_LIST Error _VN_ERROR_BL _VN_ERROR_CAL

namespace VN
{

using Errored = bool;

enum class Error : uint16_t
{
    None = 0,
    // Sensor VN Errors
    HardFault = 0x01,
    SerialBufferOverflow = 0x02,
    InvalidChecksum = 0x03,
    InvalidCommand = 0x04,
    NotEnoughParameters = 0x05,
    TooManyParameters = 0x06,
    InvalidParameter = 0x07,
    InvalidRegister = 0x08,
    UnauthorizedAccess = 0x09,
    WatchdogReset = 0x0A,
    OutputBufferOverflow = 0x0B,
    InsufficientBaudRate = 0x0C,
    ErrorBufferOverflow = 0xFF,

    // CommandProcessorErrors
    CommandResent = 301,
    CommandQueueFull = 302,
    ResponseTimeout = 303,
    ReceivedUnexpectedMessage = 304,

    // SensorErrors
    MeasurementQueueFull = 600,
    PrimaryBufferFull = 601,
    MessageSubscriberCapacityReached = 603,
    ReceivedInvalidResponse = 604,
    InvalidAccessPrimaryBuffer = 606,
    BufferFull = 607,
    AlreadyConnected = 608,

    // SerialErrors
    InvalidPortName = 700,
    AccessDenied = 701,
    SerialPortClosed = 702,
    UnsupportedBaudRate = 703,
    SerialReadFailed = 705,
    SerialWriteFailed = 706,
    UnexpectedSerialError = 799,

    // PacketSyncErrors
    ReceivedByteBufferFull = 801,
    ParsingFailed = 802,
    PacketQueueFull = 803,
    PacketQueueOverrun = 804,
    PacketQueueNull = 805,

    // FileErrors
    FileDoesNotExist = 901,
    FileOpenFailed = 902,
    FileReadFailed = 903,
    FileWriteFailed = 904,

};

inline static const char* errorCodeToString(Error error) noexcept
{
    switch (error)
    {
        case Error::None:
            return "None";
        case Error::HardFault:
            return "HardFault";
        case Error::SerialBufferOverflow:
            return "SerialBufferOverflow";
        case Error::InvalidChecksum:
            return "InvalidChecksum";
        case Error::InvalidCommand:
            return "InvalidCommand";
        case Error::NotEnoughParameters:
            return "NotEnoughParameters";
        case Error::TooManyParameters:
            return "TooManyParameters";
        case Error::InvalidParameter:
            return "InvalidParameter";
        case Error::InvalidRegister:
            return "InvalidRegister";
        case Error::UnauthorizedAccess:
            return "UnauthorizedAccess";
        case Error::WatchdogReset:
            return "WatchdogReset";
        case Error::OutputBufferOverflow:
            return "OutputBufferOverflow";
        case Error::InsufficientBaudRate:
            return "InsufficientBaudRate";
        case Error::ErrorBufferOverflow:
            return "ErrorBufferOverflow";
        case Error::PrimaryBufferFull:
            return "PrimaryBufferFull";
        case Error::CommandResent:
            return "CommandResent";
        case Error::CommandQueueFull:
            return "CommandQueueFull";
        case Error::ResponseTimeout:
            return "ResponseTimeout";
        case Error::ReceivedUnexpectedMessage:
            return "ReceivedUnexpectedMessage";
        case Error::ReceivedInvalidResponse:
            return "ReceivedInvalidResponse";
        case Error::MeasurementQueueFull:
            return "MeasurementQueueFull";
        case Error::InvalidPortName:
            return "InvalidPortName";
        case Error::AccessDenied:
            return "AccessDenied";
        case Error::SerialPortClosed:
            return "SerialPortClosed";
        case Error::UnsupportedBaudRate:
            return "UnsupportedBaudRate";
        case Error::UnexpectedSerialError:
            return "UnexpectedSerialError";
        case Error::SerialReadFailed:
            return "SerialReadFailed";
        case Error::SerialWriteFailed:
            return "SerialWriteFailed";
        case Error::MessageSubscriberCapacityReached:
            return "MessageSubscriberCapacityReached";
        case Error::ReceivedByteBufferFull:
            return "ReceivedByteBufferFull";
        case Error::ParsingFailed:
            return "ParsingFailed";
        case Error::PacketQueueFull:
            return "PacketQueueFull";
        case Error::PacketQueueOverrun:
            return "PacketQueueOverrun";
        case Error::PacketQueueNull:
            return "PacketQueueNull";
        case Error::FileDoesNotExist:
            return "FileDoesNotExist";
        case Error::FileOpenFailed:
            return "FileOpenFailed";
        case Error::FileReadFailed:
            return "FileReadFailed";
        case Error::FileWriteFailed:
            return "FileWriteFailed";
        case Error::BufferFull:
            return "BufferFull";
        case Error::AlreadyConnected:
            return "AlreadyConnected";
        case Error::InvalidAccessPrimaryBuffer:
            return "InvalidAccessPrimaryBuffer";
        default:
            return "Unknown error code.";
    }
}

template <typename T, typename... Ts>
constexpr bool is_same_any = ((std::is_same_v<T, Ts>) || ...);

template <typename T, std::enable_if_t<is_same_any<T, _VN_ERROR_LIST>, bool> = true>
inline std::ostream& operator<<(std::ostream& outStream, const T& error) noexcept
{
    outStream << "Error " << static_cast<uint16_t>(error) << ": " << errorCodeToString(error);
    return outStream;
}

struct ErrorAll
{
    ErrorAll() : ErrorAll(Error::None) {}

    static constexpr Error None = Error::None;  // enables use of ErrorAll::None

    template <typename T, std::enable_if_t<is_same_any<T, _VN_ERROR_LIST>, bool> = true>
    ErrorAll(T error)
    {
        _e = error;
        if (static_cast<uint16_t>(error) == 0) { _isNone = true; }
        else { _isNone = false; }
    }

    bool operator==(const ErrorAll& other) const { return _e == other._e; }
    bool operator!=(const ErrorAll& other) const { return _e != other._e; }

    template <typename T, std::enable_if_t<is_same_any<T, _VN_ERROR_LIST>, bool> = true>
    ErrorAll& operator=(const T& error)
    {
        this->_e = error;
        if (static_cast<uint16_t>(error) == 0) { this->_isNone = true; }
        else { this->_isNone = false; }
        return *this;
    }

    template <typename T, std::enable_if_t<is_same_any<T, _VN_ERROR_LIST>, bool> = true>
    bool operator==(const T& error) const
    {
        if (static_cast<uint16_t>(error) == 0 && _isNone) { return true; }
        else if (auto* err = std::get_if<T>(&_e)) { return *err == error; }
        else { return false; }
    }

    template <typename T, std::enable_if_t<is_same_any<T, _VN_ERROR_LIST>, bool> = true>
    bool operator!=(const T& error) const
    {
        return !(*this == error);
    }

private:
    std::variant<_VN_ERROR_LIST> _e;
    bool _isNone = false;
    friend std::ostream& operator<<(std::ostream& outStream, const ErrorAll& error) noexcept;
    friend const char* errorCodeToString(ErrorAll error) noexcept;
};
#undef _VN_ERROR_BL
#undef _VN_ERROR_CAL
#undef _VN_ERROR_LIST

inline const char* errorCodeToString(ErrorAll error) noexcept
{
    return std::visit([](auto&& arg) -> const char* { return errorCodeToString(arg); }, error._e);
}

inline std::ostream& operator<<(std::ostream& outStream, const ErrorAll& error) noexcept
{
    std::visit([&outStream](auto&& arg) { outStream << arg; }, error._e);
    return outStream;
}

template <typename EnumType, EnumType... Values>
class EnumCheck;

template <typename EnumType>
class EnumCheck<EnumType>
{
public:
    template <typename IntType>
    static bool constexpr is_value(IntType)
    {
        return false;
    }
};

template <typename EnumType, EnumType V, EnumType... Next>
class EnumCheck<EnumType, V, Next...> : private EnumCheck<EnumType, Next...>
{
    using super = EnumCheck<EnumType, Next...>;

public:
    template <typename IntType>
    static bool constexpr is_value(IntType v)
    {
        return v == static_cast<IntType>(V) || super::is_value(v);
    }
};

struct AsyncError
{
    using Message = String<Config::Errors::asyncErrorMessageCapacity>;
    AsyncError() {};
    AsyncError(const Error error) : error(error) {};
    AsyncError(const Error error, const Message& message) : error(error), message(message) {};
    AsyncError(const Error error, const time_point& timestamp) : error(error), timestamp(timestamp) {};
    AsyncError(const Error error, const Message& message, const time_point& timestamp) : error(error), message(message), timestamp(timestamp) {};

    bool operator==(const AsyncError& other) const { return error == other.error && message == other.message; }
    bool operator!=(const AsyncError& other) const { return !(*this == other); }

    Error error;
    Message message;
    time_point timestamp;
};

inline std::ostream& operator<<(std::ostream& os, const AsyncError& asyncError) noexcept
{
    os << asyncError.message << " (" << asyncError.error << ")" << "at " << asyncError.timestamp;
    return os;
}

using VnErr_Synchronous =
    EnumCheck<Error, Error::SerialBufferOverflow, Error::InvalidChecksum, Error::InvalidCommand, Error::NotEnoughParameters, Error::TooManyParameters,
              Error::InvalidParameter, Error::InvalidRegister, Error::UnauthorizedAccess, Error::InsufficientBaudRate>;

using VnErr_Asynchronous = EnumCheck<Error, Error::HardFault, Error::WatchdogReset, Error::OutputBufferOverflow, Error::ErrorBufferOverflow>;

}  // namespace VN

#endif  // VN_ERRORS_HPP_
