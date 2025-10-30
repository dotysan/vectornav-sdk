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

#ifndef VN_REGISTERS_HPP_
#define VN_REGISTERS_HPP_

#include "vectornav/Implementation/BinaryHeader.hpp"
#include "vectornav/Implementation/BinaryMeasurementDefinitions.hpp"
#include "vectornav/Interface/Commands.hpp"
#include "vectornav/TemplateLibrary/Vector.hpp"

namespace VN
{
namespace Registers
{
namespace Attitude
{
/**--------------------------------------------------------------------------------------------------
<summary> Register 8 - Yaw Pitch Roll </summary>
<remarks>

Attitude solution as yaw, pitch, and roll in degrees. The yaw, pitch, and roll is given as a 3,2,1
Euler angle rotation sequence describing the orientation of the sensor with respect to the inertial
North East Down (NED) frame.

</remarks>
*-----------------------------------------------------------------------------------------------**/
class YawPitchRoll : public MeasurementRegister
{
public:
    float yaw = 0;    ///< Yaw angle.
    float pitch = 0;  ///< Pitch angle.
    float roll = 0;   ///< Roll angle.

    YawPitchRoll() : MeasurementRegister(8) {}
    static constexpr const char* name() { return "YawPitchRoll"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    using MeasurementRegister::toString;
};

inline bool operator==(const YawPitchRoll& lhs, const YawPitchRoll& rhs)
{
    return ((lhs.yaw == rhs.yaw) && (lhs.pitch == rhs.pitch) && (lhs.roll == rhs.roll));
}

inline bool operator!=(const YawPitchRoll& lhs, const YawPitchRoll& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 9 - Quaternion </summary>
<remarks>

Attitude solution as a quaternion.

</remarks>
*-----------------------------------------------------------------------------------------------**/
class Quaternion : public MeasurementRegister
{
public:
    float quatX = 0;  ///< First vector component of quaternion.
    float quatY = 0;  ///< Second vector component of quaternion.
    float quatZ = 0;  ///< Third vector component of quaternion.
    float quatS = 0;  ///< Scalar component of quaternion.

    Quaternion() : MeasurementRegister(9) {}
    static constexpr const char* name() { return "Quaternion"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    using MeasurementRegister::toString;
};

inline bool operator==(const Quaternion& lhs, const Quaternion& rhs)
{
    return ((lhs.quatX == rhs.quatX) && (lhs.quatY == rhs.quatY) && (lhs.quatZ == rhs.quatZ) && (lhs.quatS == rhs.quatS));
}

inline bool operator!=(const Quaternion& lhs, const Quaternion& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 15 - Quaternion & Compensated IMU </summary>
<remarks>

Quaternion attitude solution, and compensated (Magnetic, Acceleration, Angular Rate) values.

</remarks>
*-----------------------------------------------------------------------------------------------**/
class QuatMagAccelRate : public MeasurementRegister
{
public:
    float quatX = 0;   ///< First vector component of quaternion.
    float quatY = 0;   ///< Second vector component of quaternion.
    float quatZ = 0;   ///< Third vector component of quaternion.
    float quatS = 0;   ///< Scalar component of quaternion.
    float magX = 0;    ///< Compensated magnetometer measurement in the body-frame x-axis.
    float magY = 0;    ///< Compensated magnetometer measurement in the body-frame y-axis.
    float magZ = 0;    ///< Compensated magnetometer measurement in the body-frame z-axis.
    float accelX = 0;  ///< Compensated accelerometer measurement in the body-frame x-axis.
    float accelY = 0;  ///< Compensated accelerometer measurement in the body-frame y-axis.
    float accelZ = 0;  ///< Compensated accelerometer measurement in the body-frame z-axis.
    float gyroX = 0;   ///< Compensated angular rate measurement in the body-frame x-axis.
    float gyroY = 0;   ///< Compensated angular rate measurement in the body-frame y-axis.
    float gyroZ = 0;   ///< Compensated angular rate measurement in the body-frame z-axis.

    QuatMagAccelRate() : MeasurementRegister(15) {}
    static constexpr const char* name() { return "QuatMagAccelRate"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    using MeasurementRegister::toString;
};

inline bool operator==(const QuatMagAccelRate& lhs, const QuatMagAccelRate& rhs)
{
    return ((lhs.quatX == rhs.quatX) && (lhs.quatY == rhs.quatY) && (lhs.quatZ == rhs.quatZ) && (lhs.quatS == rhs.quatS) && (lhs.magX == rhs.magX) &&
            (lhs.magY == rhs.magY) && (lhs.magZ == rhs.magZ) && (lhs.accelX == rhs.accelX) && (lhs.accelY == rhs.accelY) && (lhs.accelZ == rhs.accelZ) &&
            (lhs.gyroX == rhs.gyroX) && (lhs.gyroY == rhs.gyroY) && (lhs.gyroZ == rhs.gyroZ));
}

inline bool operator!=(const QuatMagAccelRate& lhs, const QuatMagAccelRate& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 21 - Magnetic and Gravity Reference Vectors </summary>
<remarks>
</remarks>
*-----------------------------------------------------------------------------------------------**/
class MagGravRefVec : public ConfigurationRegister
{
public:
    std::optional<float> magRefN;
    std::optional<float> magRefE;
    std::optional<float> magRefD;
    std::optional<float> gravRefN;
    std::optional<float> gravRefE;
    std::optional<float> gravRefD;

    MagGravRefVec() : ConfigurationRegister(21) {}
    static constexpr const char* name() { return "MagGravRefVec"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    AsciiMessage toString() const override;
};

inline bool operator==(const MagGravRefVec& lhs, const MagGravRefVec& rhs)
{
    return ((lhs.magRefN == rhs.magRefN) && (lhs.magRefE == rhs.magRefE) && (lhs.magRefD == rhs.magRefD) && (lhs.gravRefN == rhs.gravRefN) &&
            (lhs.gravRefE == rhs.gravRefE) && (lhs.gravRefD == rhs.gravRefD));
}

inline bool operator!=(const MagGravRefVec& lhs, const MagGravRefVec& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 27 - Yaw-Pitch-Roll & Compensated IMU </summary>
<remarks>

Yaw, Pitch, Roll, Accel, and Angular Rates

</remarks>
*-----------------------------------------------------------------------------------------------**/
class YprMagAccelAngularRates : public MeasurementRegister
{
public:
    float yaw = 0;     ///< Yaw angle.
    float pitch = 0;   ///< Pitch angle.
    float roll = 0;    ///< Roll angle.
    float magX = 0;    ///< Compensated magnetometer measurement in the body-frame x-axis.
    float magY = 0;    ///< Compensated magnetometer measurement in the body-frame y-axis.
    float magZ = 0;    ///< Compensated magnetometer measurement in the body-frame z-axis.
    float accelX = 0;  ///< Compensated accelerometer measurement in the body-frame x-axis.
    float accelY = 0;  ///< Compensated accelerometer measurement in the body-frame y-axis.
    float accelZ = 0;  ///< Compensated accelerometer measurement in the body-frame z-axis.
    float gyroX = 0;   ///< Compensated angular rate measurement in the body-frame x-axis.
    float gyroY = 0;   ///< Compensated angular rate measurement in the body-frame y-axis.
    float gyroZ = 0;   ///< Compensated angular rate measurement in the body-frame z-axis.

    YprMagAccelAngularRates() : MeasurementRegister(27) {}
    static constexpr const char* name() { return "YprMagAccelAngularRates"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    using MeasurementRegister::toString;
};

inline bool operator==(const YprMagAccelAngularRates& lhs, const YprMagAccelAngularRates& rhs)
{
    return ((lhs.yaw == rhs.yaw) && (lhs.pitch == rhs.pitch) && (lhs.roll == rhs.roll) && (lhs.magX == rhs.magX) && (lhs.magY == rhs.magY) &&
            (lhs.magZ == rhs.magZ) && (lhs.accelX == rhs.accelX) && (lhs.accelY == rhs.accelY) && (lhs.accelZ == rhs.accelZ) && (lhs.gyroX == rhs.gyroX) &&
            (lhs.gyroY == rhs.gyroY) && (lhs.gyroZ == rhs.gyroZ));
}

inline bool operator!=(const YprMagAccelAngularRates& lhs, const YprMagAccelAngularRates& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 35 - VPE Basic Control </summary>
<remarks>
</remarks>
*-----------------------------------------------------------------------------------------------**/
class VpeBasicControl : public ConfigurationRegister
{
public:
    enum class HeadingMode : uint8_t
    {
        Absolute = 0,
        Relative = 1,
        Indoor = 2,
    };

    enum class FilteringMode : uint8_t
    {
        Unfiltered = 0,
        AdaptivelyFiltered = 1,
    };

    enum class TuningMode : uint8_t
    {
        Static = 0,
        Adaptive = 1,
    };

    std::optional<uint8_t> resv;
    std::optional<HeadingMode> headingMode;
    std::optional<FilteringMode> filteringMode;
    std::optional<TuningMode> tuningMode;

    VpeBasicControl() : ConfigurationRegister(35) {}
    static constexpr const char* name() { return "VpeBasicControl"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    AsciiMessage toString() const override;
};

inline bool operator==(const VpeBasicControl& lhs, const VpeBasicControl& rhs)
{
    return ((lhs.resv == rhs.resv) && (lhs.headingMode == rhs.headingMode) && (lhs.filteringMode == rhs.filteringMode) && (lhs.tuningMode == rhs.tuningMode));
}

inline bool operator!=(const VpeBasicControl& lhs, const VpeBasicControl& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 36 - VPE Magnetometer Basic Tuning </summary>
<remarks>
</remarks>
*-----------------------------------------------------------------------------------------------**/
class VpeMagBasicTuning : public ConfigurationRegister
{
public:
    std::optional<float> baseTuningX;
    std::optional<float> baseTuningY;
    std::optional<float> baseTuningZ;
    std::optional<float> adaptiveTuningX;
    std::optional<float> adaptiveTuningY;
    std::optional<float> adaptiveTuningZ;
    std::optional<float> adaptiveFilteringX;
    std::optional<float> adaptiveFilteringY;
    std::optional<float> adaptiveFilteringZ;

    VpeMagBasicTuning() : ConfigurationRegister(36) {}
    static constexpr const char* name() { return "VpeMagBasicTuning"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    AsciiMessage toString() const override;
};

inline bool operator==(const VpeMagBasicTuning& lhs, const VpeMagBasicTuning& rhs)
{
    return ((lhs.baseTuningX == rhs.baseTuningX) && (lhs.baseTuningY == rhs.baseTuningY) && (lhs.baseTuningZ == rhs.baseTuningZ) &&
            (lhs.adaptiveTuningX == rhs.adaptiveTuningX) && (lhs.adaptiveTuningY == rhs.adaptiveTuningY) && (lhs.adaptiveTuningZ == rhs.adaptiveTuningZ) &&
            (lhs.adaptiveFilteringX == rhs.adaptiveFilteringX) && (lhs.adaptiveFilteringY == rhs.adaptiveFilteringY) &&
            (lhs.adaptiveFilteringZ == rhs.adaptiveFilteringZ));
}

inline bool operator!=(const VpeMagBasicTuning& lhs, const VpeMagBasicTuning& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 38 - VPE Accelerometer Basic Tuning </summary>
<remarks>
</remarks>
*-----------------------------------------------------------------------------------------------**/
class VpeAccelBasicTuning : public ConfigurationRegister
{
public:
    std::optional<float> baseTuningX;
    std::optional<float> baseTuningY;
    std::optional<float> baseTuningZ;
    std::optional<float> adaptiveTuningX;
    std::optional<float> adaptiveTuningY;
    std::optional<float> adaptiveTuningZ;
    std::optional<float> adaptiveFilteringX;
    std::optional<float> adaptiveFilteringY;
    std::optional<float> adaptiveFilteringZ;

    VpeAccelBasicTuning() : ConfigurationRegister(38) {}
    static constexpr const char* name() { return "VpeAccelBasicTuning"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    AsciiMessage toString() const override;
};

inline bool operator==(const VpeAccelBasicTuning& lhs, const VpeAccelBasicTuning& rhs)
{
    return ((lhs.baseTuningX == rhs.baseTuningX) && (lhs.baseTuningY == rhs.baseTuningY) && (lhs.baseTuningZ == rhs.baseTuningZ) &&
            (lhs.adaptiveTuningX == rhs.adaptiveTuningX) && (lhs.adaptiveTuningY == rhs.adaptiveTuningY) && (lhs.adaptiveTuningZ == rhs.adaptiveTuningZ) &&
            (lhs.adaptiveFilteringX == rhs.adaptiveFilteringX) && (lhs.adaptiveFilteringY == rhs.adaptiveFilteringY) &&
            (lhs.adaptiveFilteringZ == rhs.adaptiveFilteringZ));
}

inline bool operator!=(const VpeAccelBasicTuning& lhs, const VpeAccelBasicTuning& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 239 - Yaw-Pitch-Roll, Linear Acceleration & Gyro </summary>
<remarks>

Yaw, Pitch, Roll, Linear Body Accel, and Angular Rates.

</remarks>
*-----------------------------------------------------------------------------------------------**/
class YprLinearBodyAccelAngularRates : public MeasurementRegister
{
public:
    float yaw = 0;        ///< Yaw angle.
    float pitch = 0;      ///< Pitch angle.
    float roll = 0;       ///< Roll angle.
    float linAccelX = 0;  ///< Linear acceleration in body-frame x-axis.
    float linAccelY = 0;  ///< Linear acceleration in body-frame y-axis.
    float linAccelZ = 0;  ///< Linear acceleration in body-frame z-axis.
    float gyroX = 0;      ///< Compensated angular rate measurement in the body-frame x-axis.
    float gyroY = 0;      ///< Compensated angular rate measurement in the body-frame y-axis.
    float gyroZ = 0;      ///< Compensated angular rate measurement in the body-frame z-axis.

    YprLinearBodyAccelAngularRates() : MeasurementRegister(239) {}
    static constexpr const char* name() { return "YprLinearBodyAccelAngularRates"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    using MeasurementRegister::toString;
};

inline bool operator==(const YprLinearBodyAccelAngularRates& lhs, const YprLinearBodyAccelAngularRates& rhs)
{
    return ((lhs.yaw == rhs.yaw) && (lhs.pitch == rhs.pitch) && (lhs.roll == rhs.roll) && (lhs.linAccelX == rhs.linAccelX) &&
            (lhs.linAccelY == rhs.linAccelY) && (lhs.linAccelZ == rhs.linAccelZ) && (lhs.gyroX == rhs.gyroX) && (lhs.gyroY == rhs.gyroY) &&
            (lhs.gyroZ == rhs.gyroZ));
}

inline bool operator!=(const YprLinearBodyAccelAngularRates& lhs, const YprLinearBodyAccelAngularRates& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 240 - Yaw-Pitch-Roll, Inertial Linear Acceleration & Gyro </summary>
<remarks>

Yaw, Pitch, Roll, Linear Inertial Accel, and Angular Rates.

</remarks>
*-----------------------------------------------------------------------------------------------**/
class YprLinearInertialAccelAngularRates : public MeasurementRegister
{
public:
    float yaw = 0;        ///< Yaw angle.
    float pitch = 0;      ///< Pitch angle.
    float roll = 0;       ///< Roll angle.
    float linAccelN = 0;  ///< Linear acceleration in North direction.
    float linAccelE = 0;  ///< Linear acceleration in East direction.
    float linAccelD = 0;  ///< Linear acceleration in Down direction.
    float gyroX = 0;      ///< Compensated angular rate measurement in the body-frame x-axis.
    float gyroY = 0;      ///< Compensated angular rate measurement in the body-frame y-axis.
    float gyroZ = 0;      ///< Compensated angular rate measurement in the body-frame z-axis.

    YprLinearInertialAccelAngularRates() : MeasurementRegister(240) {}
    static constexpr const char* name() { return "YprLinearInertialAccelAngularRates"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    using MeasurementRegister::toString;
};

inline bool operator==(const YprLinearInertialAccelAngularRates& lhs, const YprLinearInertialAccelAngularRates& rhs)
{
    return ((lhs.yaw == rhs.yaw) && (lhs.pitch == rhs.pitch) && (lhs.roll == rhs.roll) && (lhs.linAccelN == rhs.linAccelN) &&
            (lhs.linAccelE == rhs.linAccelE) && (lhs.linAccelD == rhs.linAccelD) && (lhs.gyroX == rhs.gyroX) && (lhs.gyroY == rhs.gyroY) &&
            (lhs.gyroZ == rhs.gyroZ));
}

inline bool operator!=(const YprLinearInertialAccelAngularRates& lhs, const YprLinearInertialAccelAngularRates& rhs) { return !(lhs == rhs); }
}  // namespace Attitude

namespace GNSS
{
/**--------------------------------------------------------------------------------------------------
<summary> Register 55 - GNSS Basic Configuration </summary>
<remarks>
</remarks>
*-----------------------------------------------------------------------------------------------**/
class GnssBasicConfig : public ConfigurationRegister
{
public:
    enum class ReceiverEnable : uint8_t
    {
        Internal = 0,
        VnWrite = 1,
        VnAdor = 2,
        GnssA = 100,
        VnWriteAndGnssA = 101,
        VnAdorAndGnssA = 102,
        VnWriteAndGnssAB = 201,
        VnAdorAndGnssAB = 202,
    };

    enum class PpsSource : uint8_t
    {
        PpsPinRising = 0,
        PpsPinFalling = 1,
        SyncInRising = 2,
        SyncInFalling = 3,
        None = 6,
    };

    enum class Rate : uint8_t
    {
        Rate1Hz = 1,
        Rate5Hz = 5,
    };

    enum class AntPower : uint8_t
    {
        Off = 0,
        Internal = 1,
        External = 2,
    };

    std::optional<ReceiverEnable> receiverEnable;
    std::optional<PpsSource> ppsSource;
    std::optional<Rate> rate;
    std::optional<uint8_t> resv4;
    std::optional<AntPower> antPower;

    GnssBasicConfig() : ConfigurationRegister(55) {}
    static constexpr const char* name() { return "GnssBasicConfig"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    AsciiMessage toString() const override;
};

inline bool operator==(const GnssBasicConfig& lhs, const GnssBasicConfig& rhs)
{
    return ((lhs.receiverEnable == rhs.receiverEnable) && (lhs.ppsSource == rhs.ppsSource) && (lhs.rate == rhs.rate) && (lhs.resv4 == rhs.resv4) &&
            (lhs.antPower == rhs.antPower));
}

inline bool operator!=(const GnssBasicConfig& lhs, const GnssBasicConfig& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 57 - GNSS Internal A Antenna Offset </summary>
<remarks>
</remarks>
*-----------------------------------------------------------------------------------------------**/
class GnssAOffset : public ConfigurationRegister
{
public:
    std::optional<float> positionX;
    std::optional<float> positionY;
    std::optional<float> positionZ;

    GnssAOffset() : ConfigurationRegister(57) {}
    static constexpr const char* name() { return "GnssAOffset"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    AsciiMessage toString() const override;
};

inline bool operator==(const GnssAOffset& lhs, const GnssAOffset& rhs)
{
    return ((lhs.positionX == rhs.positionX) && (lhs.positionY == rhs.positionY) && (lhs.positionZ == rhs.positionZ));
}

inline bool operator!=(const GnssAOffset& lhs, const GnssAOffset& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 58 - GNSS Solution - LLA </summary>
<remarks>

Primary GNSS receiver measurement with lat/lon/alt position and velocity in NED frame.

</remarks>
*-----------------------------------------------------------------------------------------------**/
class GnssSolLla : public ConfigurationRegister
{
public:
    enum class Gnss1Fix : uint8_t
    {
        NoFix = 0,     ///< Not tracking.
        TimeFix = 1,   ///< Time-only fix.
        Fix2D = 2,     ///< Time plus 2D position fix.
        Fix3D = 3,     ///< Time plus full 3D position fix.
        SBAS = 4,      ///< 3D Fix using SBAS corrections.
        RtkFloat = 7,  ///< 3D Fix using an approximate RTK solution.
        RtkFix = 8,    ///< 3D Fix using a fixed RTK solution.
    };

    double gps1Tow = 0;     ///< GPS time of week.
    uint16_t gps1Week = 0;  ///< The current GPS week.
    Gnss1Fix gnss1Fix{0};
    uint8_t gnss1NumSats = 0;        ///< Number of satellites tracked by GNSS receiver.
    double gnss1Lat = 0;             ///< GNSS geodetic latitude.
    double gnss1Lon = 0;             ///< GNSS longitude.
    double gnss1Alt = 0;             ///< GNSS altitude above WGS84 ellipsoid.
    float gnss1VelN = 0;             ///< GNSS velocity in North direction.
    float gnss1VelE = 0;             ///< GNSS velocity in East direction.
    float gnss1VelD = 0;             ///< GNSS velocity in Down direction.
    float gnss1PosUncertaintyN = 0;  ///< GNSS position uncertainty, North direction.
    float gnss1PosUncertaintyE = 0;  ///< GNSS position uncertainty, East direction.
    float gnss1PosUncertaintyD = 0;  ///< GNSS position uncertainty, Down direction.
    float gnss1VelUncertainty = 0;   ///< GNSS velocity uncertainty (scalar).
    float gnss1TimeUncertainty = 0;  ///< GNSS time uncertainty.

    GnssSolLla() : ConfigurationRegister(58) {}
    static constexpr const char* name() { return "GnssSolLla"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    AsciiMessage toString() const override;
};

inline bool operator==(const GnssSolLla& lhs, const GnssSolLla& rhs)
{
    return ((lhs.gps1Tow == rhs.gps1Tow) && (lhs.gps1Week == rhs.gps1Week) && (lhs.gnss1Fix == rhs.gnss1Fix) && (lhs.gnss1NumSats == rhs.gnss1NumSats) &&
            (lhs.gnss1Lat == rhs.gnss1Lat) && (lhs.gnss1Lon == rhs.gnss1Lon) && (lhs.gnss1Alt == rhs.gnss1Alt) && (lhs.gnss1VelN == rhs.gnss1VelN) &&
            (lhs.gnss1VelE == rhs.gnss1VelE) && (lhs.gnss1VelD == rhs.gnss1VelD) && (lhs.gnss1PosUncertaintyN == rhs.gnss1PosUncertaintyN) &&
            (lhs.gnss1PosUncertaintyE == rhs.gnss1PosUncertaintyE) && (lhs.gnss1PosUncertaintyD == rhs.gnss1PosUncertaintyD) &&
            (lhs.gnss1VelUncertainty == rhs.gnss1VelUncertainty) && (lhs.gnss1TimeUncertainty == rhs.gnss1TimeUncertainty));
}

inline bool operator!=(const GnssSolLla& lhs, const GnssSolLla& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 59 - GNSS Solution - ECEF </summary>
<remarks>

Primary GNSS receiver measurement in ECEF frame.

</remarks>
*-----------------------------------------------------------------------------------------------**/
class GnssSolEcef : public ConfigurationRegister
{
public:
    enum class Gnss1Fix : uint8_t
    {
        NoFix = 0,     ///< Not tracking.
        TimeFix = 1,   ///< Time-only fix.
        Fix2D = 2,     ///< Time plus 2D position fix.
        Fix3D = 3,     ///< Time plus full 3D position fix.
        SBAS = 4,      ///< 3D Fix using SBAS corrections.
        RtkFloat = 7,  ///< 3D Fix using an approximate RTK solution.
        RtkFix = 8,    ///< 3D Fix using a fixed RTK solution.
    };

    double gps1Tow = 0;     ///< GPS time of week.
    uint16_t gps1Week = 0;  ///< The current GPS week.
    Gnss1Fix gnss1Fix{0};
    uint8_t gnss1NumSats = 0;        ///< Number of satellites tracked by GNSS receiver.
    double gnss1PosX = 0;            ///< GNSS position in ECEF-frame x-axis.
    double gnss1PosY = 0;            ///< GNSS position in ECEF-frame y-axis.
    double gnss1PosZ = 0;            ///< GNSS position in ECEF-frame z-axis.
    float gnss1VelX = 0;             ///< GNSS velocity in ECEF-frame x-axis.
    float gnss1VelY = 0;             ///< GNSS velocity in ECEF-frame y-axis.
    float gnss1VelZ = 0;             ///< GNSS velocity in ECEF-frame z-axis.
    float gnss1PosUncertaintyX = 0;  ///< GNSS position uncertainty ECEF X.
    float gnss1PosUncertaintyY = 0;  ///< GNSS position uncertainty ECEF Y.
    float gnss1PosUncertaintyZ = 0;  ///< GNSS position uncertainty ECEF Z.
    float gnss1VelUncertainty = 0;   ///< GNSS velocity uncertainty (scalar).
    float gnss1TimeUncertainty = 0;  ///< GNSS time uncertainty.

    GnssSolEcef() : ConfigurationRegister(59) {}
    static constexpr const char* name() { return "GnssSolEcef"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    AsciiMessage toString() const override;
};

inline bool operator==(const GnssSolEcef& lhs, const GnssSolEcef& rhs)
{
    return ((lhs.gps1Tow == rhs.gps1Tow) && (lhs.gps1Week == rhs.gps1Week) && (lhs.gnss1Fix == rhs.gnss1Fix) && (lhs.gnss1NumSats == rhs.gnss1NumSats) &&
            (lhs.gnss1PosX == rhs.gnss1PosX) && (lhs.gnss1PosY == rhs.gnss1PosY) && (lhs.gnss1PosZ == rhs.gnss1PosZ) && (lhs.gnss1VelX == rhs.gnss1VelX) &&
            (lhs.gnss1VelY == rhs.gnss1VelY) && (lhs.gnss1VelZ == rhs.gnss1VelZ) && (lhs.gnss1PosUncertaintyX == rhs.gnss1PosUncertaintyX) &&
            (lhs.gnss1PosUncertaintyY == rhs.gnss1PosUncertaintyY) && (lhs.gnss1PosUncertaintyZ == rhs.gnss1PosUncertaintyZ) &&
            (lhs.gnss1VelUncertainty == rhs.gnss1VelUncertainty) && (lhs.gnss1TimeUncertainty == rhs.gnss1TimeUncertainty));
}

inline bool operator!=(const GnssSolEcef& lhs, const GnssSolEcef& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 99 - GNSS System Configuration </summary>
<remarks>
</remarks>
*-----------------------------------------------------------------------------------------------**/
class GnssSystemConfig : public ConfigurationRegister
{
public:
    struct Systems
    {
        uint16_t gps : 1;
        uint16_t sbas : 1;
        uint16_t glonass : 1;
        uint16_t beidou : 1;
        uint16_t galileo : 1;
        uint16_t imes : 1;
        uint16_t qzssL1Ca : 1;
        uint16_t qzssL1Saif : 1;
        uint16_t : 8;  // padding

        Systems() noexcept : Systems(0) {}
        Systems(uint16_t in) noexcept { std::memcpy(this, &in, sizeof(Systems)); }

        explicit operator uint16_t() const
        {
            uint16_t result;
            std::memcpy(&result, this, sizeof(Systems));
            return result;
        }

        Systems& operator=(const uint16_t& other)
        {
            std::memcpy(this, &other, sizeof(Systems));
            return *this;
        }
    };
    static_assert(sizeof(Systems) == 2);

    struct SbasMode
    {
        uint8_t ranging : 1;
        uint8_t diffCorr : 1;
        uint8_t integrity : 1;
        uint8_t testMode : 1;
        uint8_t : 4;  // padding

        SbasMode() noexcept : SbasMode(0) {}
        SbasMode(uint8_t in) noexcept { std::memcpy(this, &in, sizeof(SbasMode)); }

        explicit operator uint8_t() const
        {
            uint8_t result;
            std::memcpy(&result, this, sizeof(SbasMode));
            return result;
        }

        SbasMode& operator=(const uint8_t& other)
        {
            std::memcpy(this, &other, sizeof(SbasMode));
            return *this;
        }
    };
    static_assert(sizeof(SbasMode) == 1);

    struct SbasSelect1
    {
        uint16_t sbas120 : 1;
        uint16_t sbas121 : 1;
        uint16_t sbas122 : 1;
        uint16_t sbas123 : 1;
        uint16_t sbas124 : 1;
        uint16_t sbas125 : 1;
        uint16_t sbas126 : 1;
        uint16_t sbas127 : 1;
        uint16_t sbas128 : 1;
        uint16_t sbas129 : 1;
        uint16_t sbas130 : 1;
        uint16_t sbas131 : 1;
        uint16_t sbas132 : 1;
        uint16_t sbas133 : 1;
        uint16_t sbas134 : 1;
        uint16_t sbas135 : 1;
        uint16_t : 0;  // padding

        SbasSelect1() noexcept : SbasSelect1(0) {}
        SbasSelect1(uint16_t in) noexcept { std::memcpy(this, &in, sizeof(SbasSelect1)); }

        explicit operator uint16_t() const
        {
            uint16_t result;
            std::memcpy(&result, this, sizeof(SbasSelect1));
            return result;
        }

        SbasSelect1& operator=(const uint16_t& other)
        {
            std::memcpy(this, &other, sizeof(SbasSelect1));
            return *this;
        }
    };
    static_assert(sizeof(SbasSelect1) == 2);

    struct SbasSelect2
    {
        uint16_t sbas136 : 1;
        uint16_t sbas137 : 1;
        uint16_t sbas138 : 1;
        uint16_t sbas139 : 1;
        uint16_t sbas140 : 1;
        uint16_t sbas141 : 1;
        uint16_t sbas142 : 1;
        uint16_t sbas143 : 1;
        uint16_t sbas144 : 1;
        uint16_t sbas145 : 1;
        uint16_t sbas146 : 1;
        uint16_t sbas147 : 1;
        uint16_t sbas148 : 1;
        uint16_t sbas149 : 1;
        uint16_t sbas150 : 1;
        uint16_t sbas151 : 1;
        uint16_t : 0;  // padding

        SbasSelect2() noexcept : SbasSelect2(0) {}
        SbasSelect2(uint16_t in) noexcept { std::memcpy(this, &in, sizeof(SbasSelect2)); }

        explicit operator uint16_t() const
        {
            uint16_t result;
            std::memcpy(&result, this, sizeof(SbasSelect2));
            return result;
        }

        SbasSelect2& operator=(const uint16_t& other)
        {
            std::memcpy(this, &other, sizeof(SbasSelect2));
            return *this;
        }
    };
    static_assert(sizeof(SbasSelect2) == 2);

    struct SbasSelect3
    {
        uint16_t sbas152 : 1;
        uint16_t sbas153 : 1;
        uint16_t sbas154 : 1;
        uint16_t sbas155 : 1;
        uint16_t sbas156 : 1;
        uint16_t sbas157 : 1;
        uint16_t sbas158 : 1;
        uint16_t : 9;  // padding

        SbasSelect3() noexcept : SbasSelect3(0) {}
        SbasSelect3(uint16_t in) noexcept { std::memcpy(this, &in, sizeof(SbasSelect3)); }

        explicit operator uint16_t() const
        {
            uint16_t result;
            std::memcpy(&result, this, sizeof(SbasSelect3));
            return result;
        }

        SbasSelect3& operator=(const uint16_t& other)
        {
            std::memcpy(this, &other, sizeof(SbasSelect3));
            return *this;
        }
    };
    static_assert(sizeof(SbasSelect3) == 2);

    enum class ReceiverSelect : uint8_t
    {
        GnssAB = 0,
        GnssA = 1,
        GnssB = 2,
    };

    std::optional<Systems> systems;
    std::optional<uint8_t> minCno;
    std::optional<uint8_t> minElev;
    std::optional<uint8_t> maxSats;
    std::optional<SbasMode> sbasMode;
    std::optional<SbasSelect1> sbasSelect1;
    std::optional<SbasSelect2> sbasSelect2;
    std::optional<SbasSelect3> sbasSelect3;
    ReceiverSelect receiverSelect{0};

    GnssSystemConfig() : ConfigurationRegister(99) {}
    static constexpr const char* name() { return "GnssSystemConfig"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    AsciiMessage toString() const override;
    GenericCommand toReadCommand() override;
};

inline bool operator==(const GnssSystemConfig::Systems& lhs, const GnssSystemConfig::Systems& rhs) noexcept
{
    return static_cast<uint16_t>(lhs) == static_cast<uint16_t>(rhs);
}
inline bool operator!=(const GnssSystemConfig::Systems& lhs, const GnssSystemConfig::Systems& rhs) noexcept { return !(lhs == rhs); }

inline bool operator==(const GnssSystemConfig::SbasMode& lhs, const GnssSystemConfig::SbasMode& rhs) noexcept
{
    return static_cast<uint8_t>(lhs) == static_cast<uint8_t>(rhs);
}
inline bool operator!=(const GnssSystemConfig::SbasMode& lhs, const GnssSystemConfig::SbasMode& rhs) noexcept { return !(lhs == rhs); }

inline bool operator==(const GnssSystemConfig::SbasSelect1& lhs, const GnssSystemConfig::SbasSelect1& rhs) noexcept
{
    return static_cast<uint16_t>(lhs) == static_cast<uint16_t>(rhs);
}
inline bool operator!=(const GnssSystemConfig::SbasSelect1& lhs, const GnssSystemConfig::SbasSelect1& rhs) noexcept { return !(lhs == rhs); }

inline bool operator==(const GnssSystemConfig::SbasSelect2& lhs, const GnssSystemConfig::SbasSelect2& rhs) noexcept
{
    return static_cast<uint16_t>(lhs) == static_cast<uint16_t>(rhs);
}
inline bool operator!=(const GnssSystemConfig::SbasSelect2& lhs, const GnssSystemConfig::SbasSelect2& rhs) noexcept { return !(lhs == rhs); }

inline bool operator==(const GnssSystemConfig::SbasSelect3& lhs, const GnssSystemConfig::SbasSelect3& rhs) noexcept
{
    return static_cast<uint16_t>(lhs) == static_cast<uint16_t>(rhs);
}
inline bool operator!=(const GnssSystemConfig::SbasSelect3& lhs, const GnssSystemConfig::SbasSelect3& rhs) noexcept { return !(lhs == rhs); }

inline bool operator==(const GnssSystemConfig& lhs, const GnssSystemConfig& rhs)
{
    return ((lhs.systems == rhs.systems) && (lhs.minCno == rhs.minCno) && (lhs.minElev == rhs.minElev) && (lhs.maxSats == rhs.maxSats) &&
            (lhs.sbasMode == rhs.sbasMode) && (lhs.sbasSelect1 == rhs.sbasSelect1) && (lhs.sbasSelect2 == rhs.sbasSelect2) &&
            (lhs.sbasSelect3 == rhs.sbasSelect3) && (lhs.receiverSelect == rhs.receiverSelect));
}

inline bool operator!=(const GnssSystemConfig& lhs, const GnssSystemConfig& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 100 - GNSS Sync Configuration </summary>
<remarks>
</remarks>
*-----------------------------------------------------------------------------------------------**/
class GnssSyncConfig : public ConfigurationRegister
{
public:
    enum class GnssSyncEnable : uint8_t
    {
        Off = 0,
        AlwaysOn = 1,
        OnWhenLocked = 2,
    };

    enum class Polarity : uint8_t
    {
        FallingEdge = 0,
        RisingEdge = 1,
    };

    enum class SpecType : uint8_t
    {
        PeriodPulseWidth = 0,
        FreqDutyCycle = 1,
    };

    std::optional<GnssSyncEnable> gnssSyncEnable;
    std::optional<Polarity> polarity;
    std::optional<SpecType> specType;
    std::optional<uint8_t> resv;
    std::optional<uint32_t> period;
    std::optional<uint32_t> pulseWidth;
    std::optional<int32_t> offset;

    GnssSyncConfig() : ConfigurationRegister(100) {}
    static constexpr const char* name() { return "GnssSyncConfig"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    AsciiMessage toString() const override;
};

inline bool operator==(const GnssSyncConfig& lhs, const GnssSyncConfig& rhs)
{
    return ((lhs.gnssSyncEnable == rhs.gnssSyncEnable) && (lhs.polarity == rhs.polarity) && (lhs.specType == rhs.specType) && (lhs.resv == rhs.resv) &&
            (lhs.period == rhs.period) && (lhs.pulseWidth == rhs.pulseWidth) && (lhs.offset == rhs.offset));
}

inline bool operator!=(const GnssSyncConfig& lhs, const GnssSyncConfig& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 103 - GNSS 2 Solution - LLA </summary>
<remarks>

Estimated GNSS 2 Solution with lat/lon/alt position. This register is deprecated and will be
removed in future firmware versions.

</remarks>
*-----------------------------------------------------------------------------------------------**/
class Gnss2SolLla : public MeasurementRegister
{
public:
    enum class Gnss2Fix : uint8_t
    {
        NoFix = 0,     ///< Not tracking.
        TimeFix = 1,   ///< Time-only fix.
        Fix2D = 2,     ///< Time plus 2D position fix.
        Fix3D = 3,     ///< Time plus full 3D position fix.
        SBAS = 4,      ///< 3D Fix using SBAS corrections.
        RtkFloat = 7,  ///< 3D Fix using an approximate RTK solution.
        RtkFix = 8,    ///< 3D Fix using a fixed RTK solution.
    };

    double gps2Tow = 0;     ///< GPS time of week.
    uint16_t gps2Week = 0;  ///< The current GPS week.
    Gnss2Fix gnss2Fix{0};
    uint8_t gnss2NumSats = 0;        ///< Number of satellites tracked by GNSS receiver.
    double gnss2Lat = 0;             ///< GNSS geodetic latitude.
    double gnss2Lon = 0;             ///< GNSS longitude.
    double gnss2Alt = 0;             ///< GNSS altitude above WGS84 ellipsoid.
    float gnss2VelN = 0;             ///< GNSS velocity in North direction.
    float gnss2VelE = 0;             ///< GNSS velocity in East direction.
    float gnss2VelD = 0;             ///< GNSS velocity in Down direction.
    float gnss2PosUncertaintyN = 0;  ///< GNSS position uncertainty, North direction.
    float gnss2PosUncertaintyE = 0;  ///< GNSS position uncertainty, East direction.
    float gnss2PosUncertaintyD = 0;  ///< GNSS position uncertainty, Down direction.
    float gnss2VelUncertainty = 0;   ///< GNSS velocity uncertainty (scalar).
    float gnss2TimeUncertainty = 0;  ///< GNSS time uncertainty.

    Gnss2SolLla() : MeasurementRegister(103) {}
    static constexpr const char* name() { return "Gnss2SolLla"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    using MeasurementRegister::toString;
};

inline bool operator==(const Gnss2SolLla& lhs, const Gnss2SolLla& rhs)
{
    return ((lhs.gps2Tow == rhs.gps2Tow) && (lhs.gps2Week == rhs.gps2Week) && (lhs.gnss2Fix == rhs.gnss2Fix) && (lhs.gnss2NumSats == rhs.gnss2NumSats) &&
            (lhs.gnss2Lat == rhs.gnss2Lat) && (lhs.gnss2Lon == rhs.gnss2Lon) && (lhs.gnss2Alt == rhs.gnss2Alt) && (lhs.gnss2VelN == rhs.gnss2VelN) &&
            (lhs.gnss2VelE == rhs.gnss2VelE) && (lhs.gnss2VelD == rhs.gnss2VelD) && (lhs.gnss2PosUncertaintyN == rhs.gnss2PosUncertaintyN) &&
            (lhs.gnss2PosUncertaintyE == rhs.gnss2PosUncertaintyE) && (lhs.gnss2PosUncertaintyD == rhs.gnss2PosUncertaintyD) &&
            (lhs.gnss2VelUncertainty == rhs.gnss2VelUncertainty) && (lhs.gnss2TimeUncertainty == rhs.gnss2TimeUncertainty));
}

inline bool operator!=(const Gnss2SolLla& lhs, const Gnss2SolLla& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 104 - GNSS 2 Solution - ECEF </summary>
<remarks>

Estimated GNSS 2 Solution with ECEF position. This register is deprecated and will be removed in
future firmware versions.

</remarks>
*-----------------------------------------------------------------------------------------------**/
class Gnss2SolEcef : public MeasurementRegister
{
public:
    enum class Gnss2Fix : uint8_t
    {
        NoFix = 0,     ///< Not tracking.
        TimeFix = 1,   ///< Time-only fix.
        Fix2D = 2,     ///< Time plus 2D position fix.
        Fix3D = 3,     ///< Time plus full 3D position fix.
        SBAS = 4,      ///< 3D Fix using SBAS corrections.
        RtkFloat = 7,  ///< 3D Fix using an approximate RTK solution.
        RtkFix = 8,    ///< 3D Fix using a fixed RTK solution.
    };

    double gps2Tow = 0;     ///< GPS time of week.
    uint16_t gps2Week = 0;  ///< The current GPS week.
    Gnss2Fix gnss2Fix{0};
    uint8_t gnss2NumSats = 0;        ///< Number of satellites tracked by GNSS receiver.
    double gnss2PosX = 0;            ///< GNSS position in ECEF-frame x-axis.
    double gnss2PosY = 0;            ///< GNSS position in ECEF-frame y-axis.
    double gnss2PosZ = 0;            ///< GNSS position in ECEF-frame z-axis.
    float gnss2VelX = 0;             ///< GNSS velocity in ECEF-frame x-axis.
    float gnss2VelY = 0;             ///< GNSS velocity in ECEF-frame y-axis.
    float gnss2VelZ = 0;             ///< GNSS velocity in ECEF-frame z-axis.
    float gnss2PosUncertaintyX = 0;  ///< GNSS position uncertainty ECEF X.
    float gnss2PosUncertaintyY = 0;  ///< GNSS position uncertainty ECEF Y.
    float gnss2PosUncertaintyZ = 0;  ///< GNSS position uncertainty ECEF Z.
    float gnss2VelUncertainty = 0;   ///< GNSS velocity uncertainty (scalar).
    float gnss2TimeUncertainty = 0;  ///< GNSS time uncertainty.

    Gnss2SolEcef() : MeasurementRegister(104) {}
    static constexpr const char* name() { return "Gnss2SolEcef"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    using MeasurementRegister::toString;
};

inline bool operator==(const Gnss2SolEcef& lhs, const Gnss2SolEcef& rhs)
{
    return ((lhs.gps2Tow == rhs.gps2Tow) && (lhs.gps2Week == rhs.gps2Week) && (lhs.gnss2Fix == rhs.gnss2Fix) && (lhs.gnss2NumSats == rhs.gnss2NumSats) &&
            (lhs.gnss2PosX == rhs.gnss2PosX) && (lhs.gnss2PosY == rhs.gnss2PosY) && (lhs.gnss2PosZ == rhs.gnss2PosZ) && (lhs.gnss2VelX == rhs.gnss2VelX) &&
            (lhs.gnss2VelY == rhs.gnss2VelY) && (lhs.gnss2VelZ == rhs.gnss2VelZ) && (lhs.gnss2PosUncertaintyX == rhs.gnss2PosUncertaintyX) &&
            (lhs.gnss2PosUncertaintyY == rhs.gnss2PosUncertaintyY) && (lhs.gnss2PosUncertaintyZ == rhs.gnss2PosUncertaintyZ) &&
            (lhs.gnss2VelUncertainty == rhs.gnss2VelUncertainty) && (lhs.gnss2TimeUncertainty == rhs.gnss2TimeUncertainty));
}

inline bool operator!=(const Gnss2SolEcef& lhs, const Gnss2SolEcef& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 157 - External GNSS Antenna Offset </summary>
<remarks>
</remarks>
*-----------------------------------------------------------------------------------------------**/
class ExtGnssOffset : public ConfigurationRegister
{
public:
    std::optional<float> positionX;
    std::optional<float> positionY;
    std::optional<float> positionZ;

    ExtGnssOffset() : ConfigurationRegister(157) {}
    static constexpr const char* name() { return "ExtGnssOffset"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    AsciiMessage toString() const override;
};

inline bool operator==(const ExtGnssOffset& lhs, const ExtGnssOffset& rhs)
{
    return ((lhs.positionX == rhs.positionX) && (lhs.positionY == rhs.positionY) && (lhs.positionZ == rhs.positionZ));
}

inline bool operator!=(const ExtGnssOffset& lhs, const ExtGnssOffset& rhs) { return !(lhs == rhs); }
}  // namespace GNSS

namespace GNSSCompass
{
/**--------------------------------------------------------------------------------------------------
<summary> Register 86 - GNSS Compass Signal Health Status </summary>
<remarks>

Provides several indicators that serve as an overall health status of the GNSS compass subsystem.

</remarks>
*-----------------------------------------------------------------------------------------------**/
class GnssCompassSignalHealthStatus : public MeasurementRegister
{
public:
    float numSatsPvtA = 0;    ///< Number of satellites available for PVT solution for receiver A.
    float numSatsRtkA = 0;    ///< Number of satellites available for RTK solution for receiver A.
    float highestCn0A = 0;    ///< Highest CN0 reported on receiver A.
    float numSatsPvtB = 0;    ///< Number of satellites available for the PVT solution of receiver B.
    float numSatsRtkB = 0;    ///< Number of satellites available for the RTK solution of receiver B.
    float highestCn0B = 0;    ///< Highest CN0 reported on receiver B.
    float numComSatsPvt = 0;  ///< The number of common satellites that are used in the PVT solutions of both receiver A and receiver B.
    float numComSatsRtk = 0;  ///< The number of common satellites that are used in the RTK solutions of both receiver A and receiver B.

    GnssCompassSignalHealthStatus() : MeasurementRegister(86) {}
    static constexpr const char* name() { return "GnssCompassSignalHealthStatus"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    using MeasurementRegister::toString;
};

inline bool operator==(const GnssCompassSignalHealthStatus& lhs, const GnssCompassSignalHealthStatus& rhs)
{
    return ((lhs.numSatsPvtA == rhs.numSatsPvtA) && (lhs.numSatsRtkA == rhs.numSatsRtkA) && (lhs.highestCn0A == rhs.highestCn0A) &&
            (lhs.numSatsPvtB == rhs.numSatsPvtB) && (lhs.numSatsRtkB == rhs.numSatsRtkB) && (lhs.highestCn0B == rhs.highestCn0B) &&
            (lhs.numComSatsPvt == rhs.numComSatsPvt) && (lhs.numComSatsRtk == rhs.numComSatsRtk));
}

inline bool operator!=(const GnssCompassSignalHealthStatus& lhs, const GnssCompassSignalHealthStatus& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 93 - GNSS Compass Antenna Baseline </summary>
<remarks>
</remarks>
*-----------------------------------------------------------------------------------------------**/
class GnssCompassBaseline : public ConfigurationRegister
{
public:
    std::optional<float> positionX;
    std::optional<float> positionY;
    std::optional<float> positionZ;
    std::optional<float> uncertaintyX;
    std::optional<float> uncertaintyY;
    std::optional<float> uncertaintyZ;

    GnssCompassBaseline() : ConfigurationRegister(93) {}
    static constexpr const char* name() { return "GnssCompassBaseline"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    AsciiMessage toString() const override;
};

inline bool operator==(const GnssCompassBaseline& lhs, const GnssCompassBaseline& rhs)
{
    return ((lhs.positionX == rhs.positionX) && (lhs.positionY == rhs.positionY) && (lhs.positionZ == rhs.positionZ) &&
            (lhs.uncertaintyX == rhs.uncertaintyX) && (lhs.uncertaintyY == rhs.uncertaintyY) && (lhs.uncertaintyZ == rhs.uncertaintyZ));
}

inline bool operator!=(const GnssCompassBaseline& lhs, const GnssCompassBaseline& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 97 - GNSS Compass Estimated Baseline </summary>
<remarks>

Provides the estimated GNSS compass baseline measurement. The estimated position offset and
measurement uncertainty is for antenna B relative to antenna A in the body reference frame.

</remarks>
*-----------------------------------------------------------------------------------------------**/
class GnssCompassEstBaseline : public MeasurementRegister
{
public:
    uint8_t estBaselineComplete = 0;  ///< Set to 1 when baseline estimation has complete.
    uint8_t resv = 0;                 ///< Reserved.
    uint16_t numMeas = 0;             ///< Number of measurements used by the estimated solution.
    float positionX = 0;              ///< Position of GNSS antenna B with respect to antenna A in the body-frame x-axis.
    float positionY = 0;              ///< Position of GNSS antenna B with respect to antenna A in the body-frame y-axis.
    float positionZ = 0;              ///< Position of GNSS antenna B with respect to antenna A in the body-frame z-axis.
    float uncertaintyX = 0;           ///< Uncertainty in the x-axis position measurement.
    float uncertaintyY = 0;           ///< Uncertainty in the y-axis position measurement.
    float uncertaintyZ = 0;           ///< Uncertainty in the z-axis position measurement.

    GnssCompassEstBaseline() : MeasurementRegister(97) {}
    static constexpr const char* name() { return "GnssCompassEstBaseline"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    using MeasurementRegister::toString;
};

inline bool operator==(const GnssCompassEstBaseline& lhs, const GnssCompassEstBaseline& rhs)
{
    return ((lhs.estBaselineComplete == rhs.estBaselineComplete) && (lhs.resv == rhs.resv) && (lhs.numMeas == rhs.numMeas) &&
            (lhs.positionX == rhs.positionX) && (lhs.positionY == rhs.positionY) && (lhs.positionZ == rhs.positionZ) &&
            (lhs.uncertaintyX == rhs.uncertaintyX) && (lhs.uncertaintyY == rhs.uncertaintyY) && (lhs.uncertaintyZ == rhs.uncertaintyZ));
}

inline bool operator!=(const GnssCompassEstBaseline& lhs, const GnssCompassEstBaseline& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 98 - GNSS Compass Startup Status </summary>
<remarks>

Provides status information on the GNSS compass startup process.

</remarks>
*-----------------------------------------------------------------------------------------------**/
class GnssCompassStartupStatus : public MeasurementRegister
{
public:
    uint8_t percentComplete = 0;  ///< The estimated startup process completion percent.
    float currentHeading = 0;     ///< The current GNSS compass heading estimate.

    GnssCompassStartupStatus() : MeasurementRegister(98) {}
    static constexpr const char* name() { return "GnssCompassStartupStatus"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    using MeasurementRegister::toString;
};

inline bool operator==(const GnssCompassStartupStatus& lhs, const GnssCompassStartupStatus& rhs)
{
    return ((lhs.percentComplete == rhs.percentComplete) && (lhs.currentHeading == rhs.currentHeading));
}

inline bool operator!=(const GnssCompassStartupStatus& lhs, const GnssCompassStartupStatus& rhs) { return !(lhs == rhs); }
}  // namespace GNSSCompass

namespace HardSoftIronEstimator
{
/**--------------------------------------------------------------------------------------------------
<summary> Register 44 - Real-Time HSI Control </summary>
<remarks>
</remarks>
*-----------------------------------------------------------------------------------------------**/
class RealTimeHsiControl : public ConfigurationRegister
{
public:
    enum class Mode : uint8_t
    {
        Off = 0,
        Run = 1,
        Reset = 2,
    };

    enum class ApplyCompensation : uint8_t
    {
        Disable = 1,
        Enable = 3,
    };

    std::optional<Mode> mode;
    std::optional<ApplyCompensation> applyCompensation;
    std::optional<uint8_t> convergeRate;

    RealTimeHsiControl() : ConfigurationRegister(44) {}
    static constexpr const char* name() { return "RealTimeHsiControl"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    AsciiMessage toString() const override;
};

inline bool operator==(const RealTimeHsiControl& lhs, const RealTimeHsiControl& rhs)
{
    return ((lhs.mode == rhs.mode) && (lhs.applyCompensation == rhs.applyCompensation) && (lhs.convergeRate == rhs.convergeRate));
}

inline bool operator!=(const RealTimeHsiControl& lhs, const RealTimeHsiControl& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 47 - Real-Time HSI Results </summary>
<remarks>

Magnetometer calibration values calculated by the real-time HSI calibration filter.

</remarks>
*-----------------------------------------------------------------------------------------------**/
class EstMagCal : public MeasurementRegister
{
public:
    float magGain00 = 0;  ///< Magnetometer calibration gain matrix, row 0, colum 0.
    float magGain01 = 0;  ///< Magnetometer calibration gain matrix, row 0, colum 1.
    float magGain02 = 0;  ///< Magnetometer calibration gain matrix, row 0, colum 2.
    float magGain10 = 0;  ///< Magnetometer calibration gain matrix, row 1, colum 0.
    float magGain11 = 0;  ///< Magnetometer calibration gain matrix, row 1, colum 1.
    float magGain12 = 0;  ///< Magnetometer calibration gain matrix, row 1, colum 2.
    float magGain20 = 0;  ///< Magnetometer calibration gain matrix, row 2, colum 0.
    float magGain21 = 0;  ///< Magnetometer calibration gain matrix, row 2, colum 1.
    float magGain22 = 0;  ///< Magnetometer calibration gain matrix, row 2, colum 2.
    float magBiasX = 0;   ///< Magnetometer bias calibration, sensor-frame x-axis.
    float magBiasY = 0;   ///< Magnetometer bias calibration, sensor-frame y-axis.
    float magBiasZ = 0;   ///< Magnetometer bias calibration, sensor-frame z-axis.

    EstMagCal() : MeasurementRegister(47) {}
    static constexpr const char* name() { return "EstMagCal"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    using MeasurementRegister::toString;
};

inline bool operator==(const EstMagCal& lhs, const EstMagCal& rhs)
{
    return ((lhs.magGain00 == rhs.magGain00) && (lhs.magGain01 == rhs.magGain01) && (lhs.magGain02 == rhs.magGain02) && (lhs.magGain10 == rhs.magGain10) &&
            (lhs.magGain11 == rhs.magGain11) && (lhs.magGain12 == rhs.magGain12) && (lhs.magGain20 == rhs.magGain20) && (lhs.magGain21 == rhs.magGain21) &&
            (lhs.magGain22 == rhs.magGain22) && (lhs.magBiasX == rhs.magBiasX) && (lhs.magBiasY == rhs.magBiasY) && (lhs.magBiasZ == rhs.magBiasZ));
}

inline bool operator!=(const EstMagCal& lhs, const EstMagCal& rhs) { return !(lhs == rhs); }
}  // namespace HardSoftIronEstimator

namespace Heave
{
/**--------------------------------------------------------------------------------------------------
<summary> Register 115 - Heave and Heave Rate </summary>
<remarks>

Real-time heave and heave-rate estimates, plus a delayed-heave estimate.

</remarks>
*-----------------------------------------------------------------------------------------------**/
class HeaveOutputs : public MeasurementRegister
{
public:
    float heave = 0;         ///< Real-time heave estimate.
    float heaveRate = 0;     ///< Real-time heave rate estimate.
    float delayedHeave = 0;  ///< Delayed heave. Higher accuracy than real-time heave, but 50 seconds old.

    HeaveOutputs() : MeasurementRegister(115) {}
    static constexpr const char* name() { return "HeaveOutputs"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    using MeasurementRegister::toString;
};

inline bool operator==(const HeaveOutputs& lhs, const HeaveOutputs& rhs)
{
    return ((lhs.heave == rhs.heave) && (lhs.heaveRate == rhs.heaveRate) && (lhs.delayedHeave == rhs.delayedHeave));
}

inline bool operator!=(const HeaveOutputs& lhs, const HeaveOutputs& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 116 - Heave Basic Configuration </summary>
<remarks>
</remarks>
*-----------------------------------------------------------------------------------------------**/
class HeaveBasicConfig : public ConfigurationRegister
{
public:
    std::optional<float> initialWavePeriod;
    std::optional<float> initialWaveAmplitude;
    std::optional<float> maxWavePeriod;
    std::optional<float> minWaveAmplitude;
    std::optional<float> delayedHeaveCutoffFreq;
    std::optional<float> heaveCutoffFreq;
    std::optional<float> heaveRateCutoffFreq;

    HeaveBasicConfig() : ConfigurationRegister(116) {}
    static constexpr const char* name() { return "HeaveBasicConfig"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    AsciiMessage toString() const override;
};

inline bool operator==(const HeaveBasicConfig& lhs, const HeaveBasicConfig& rhs)
{
    return ((lhs.initialWavePeriod == rhs.initialWavePeriod) && (lhs.initialWaveAmplitude == rhs.initialWaveAmplitude) &&
            (lhs.maxWavePeriod == rhs.maxWavePeriod) && (lhs.minWaveAmplitude == rhs.minWaveAmplitude) &&
            (lhs.delayedHeaveCutoffFreq == rhs.delayedHeaveCutoffFreq) && (lhs.heaveCutoffFreq == rhs.heaveCutoffFreq) &&
            (lhs.heaveRateCutoffFreq == rhs.heaveRateCutoffFreq));
}

inline bool operator!=(const HeaveBasicConfig& lhs, const HeaveBasicConfig& rhs) { return !(lhs == rhs); }
}  // namespace Heave

namespace IMU
{
/**--------------------------------------------------------------------------------------------------
<summary> Register 17 - Compensated Magnetometer </summary>
<remarks>

Compensated magnetometer measurements.

</remarks>
*-----------------------------------------------------------------------------------------------**/
class Mag : public MeasurementRegister
{
public:
    float magX = 0;  ///< Compensated magnetometer measurement in the body-frame x-axis.
    float magY = 0;  ///< Compensated magnetometer measurement in the body-frame y-axis.
    float magZ = 0;  ///< Compensated magnetometer measurement in the body-frame z-axis.

    Mag() : MeasurementRegister(17) {}
    static constexpr const char* name() { return "Mag"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    using MeasurementRegister::toString;
};

inline bool operator==(const Mag& lhs, const Mag& rhs) { return ((lhs.magX == rhs.magX) && (lhs.magY == rhs.magY) && (lhs.magZ == rhs.magZ)); }

inline bool operator!=(const Mag& lhs, const Mag& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 18 - Compensated Accelerometer </summary>
<remarks>

Compensated acceleration measurements

</remarks>
*-----------------------------------------------------------------------------------------------**/
class Accel : public MeasurementRegister
{
public:
    float accelX = 0;  ///< Compensated accelerometer measurement in the body-frame x-axis.
    float accelY = 0;  ///< Compensated accelerometer measurement in the body-frame y-axis.
    float accelZ = 0;  ///< Compensated accelerometer measurement in the body-frame z-axis.

    Accel() : MeasurementRegister(18) {}
    static constexpr const char* name() { return "Accel"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    using MeasurementRegister::toString;
};

inline bool operator==(const Accel& lhs, const Accel& rhs) { return ((lhs.accelX == rhs.accelX) && (lhs.accelY == rhs.accelY) && (lhs.accelZ == rhs.accelZ)); }

inline bool operator!=(const Accel& lhs, const Accel& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 19 - Compensated Gyro </summary>
<remarks>

Compensated angular rate measurements.

</remarks>
*-----------------------------------------------------------------------------------------------**/
class Gyro : public MeasurementRegister
{
public:
    float gyroX = 0;  ///< Compensated angular rate measurement in the body-frame x-axis.
    float gyroY = 0;  ///< Compensated angular rate measurement in the body-frame y-axis.
    float gyroZ = 0;  ///< Compensated angular rate measurement in the body-frame z-axis.

    Gyro() : MeasurementRegister(19) {}
    static constexpr const char* name() { return "Gyro"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    using MeasurementRegister::toString;
};

inline bool operator==(const Gyro& lhs, const Gyro& rhs) { return ((lhs.gyroX == rhs.gyroX) && (lhs.gyroY == rhs.gyroY) && (lhs.gyroZ == rhs.gyroZ)); }

inline bool operator!=(const Gyro& lhs, const Gyro& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 20 - Compensated IMU </summary>
<remarks>

Compensated magnetic, acceleration, and angular rate measurements.

</remarks>
*-----------------------------------------------------------------------------------------------**/
class MagAccelGyro : public MeasurementRegister
{
public:
    float magX = 0;    ///< Compensated magnetometer measurement in the body-frame x-axis.
    float magY = 0;    ///< Compensated magnetometer measurement in the body-frame y-axis.
    float magZ = 0;    ///< Compensated magnetometer measurement in the body-frame z-axis.
    float accelX = 0;  ///< Compensated accelerometer measurement in the body-frame x-axis.
    float accelY = 0;  ///< Compensated accelerometer measurement in the body-frame y-axis.
    float accelZ = 0;  ///< Compensated accelerometer measurement in the body-frame z-axis.
    float gyroX = 0;   ///< Compensated angular rate measurement in the body-frame x-axis.
    float gyroY = 0;   ///< Compensated angular rate measurement in the body-frame y-axis.
    float gyroZ = 0;   ///< Compensated angular rate measurement in the body-frame z-axis.

    MagAccelGyro() : MeasurementRegister(20) {}
    static constexpr const char* name() { return "MagAccelGyro"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    using MeasurementRegister::toString;
};

inline bool operator==(const MagAccelGyro& lhs, const MagAccelGyro& rhs)
{
    return ((lhs.magX == rhs.magX) && (lhs.magY == rhs.magY) && (lhs.magZ == rhs.magZ) && (lhs.accelX == rhs.accelX) && (lhs.accelY == rhs.accelY) &&
            (lhs.accelZ == rhs.accelZ) && (lhs.gyroX == rhs.gyroX) && (lhs.gyroY == rhs.gyroY) && (lhs.gyroZ == rhs.gyroZ));
}

inline bool operator!=(const MagAccelGyro& lhs, const MagAccelGyro& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 23 - Magnetometer Calibration </summary>
<remarks>
</remarks>
*-----------------------------------------------------------------------------------------------**/
class MagCal : public ConfigurationRegister
{
public:
    std::optional<float> magGain00;
    std::optional<float> magGain01;
    std::optional<float> magGain02;
    std::optional<float> magGain10;
    std::optional<float> magGain11;
    std::optional<float> magGain12;
    std::optional<float> magGain20;
    std::optional<float> magGain21;
    std::optional<float> magGain22;
    std::optional<float> magBiasX;
    std::optional<float> magBiasY;
    std::optional<float> magBiasZ;

    MagCal() : ConfigurationRegister(23) {}
    static constexpr const char* name() { return "MagCal"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    AsciiMessage toString() const override;
};

inline bool operator==(const MagCal& lhs, const MagCal& rhs)
{
    return ((lhs.magGain00 == rhs.magGain00) && (lhs.magGain01 == rhs.magGain01) && (lhs.magGain02 == rhs.magGain02) && (lhs.magGain10 == rhs.magGain10) &&
            (lhs.magGain11 == rhs.magGain11) && (lhs.magGain12 == rhs.magGain12) && (lhs.magGain20 == rhs.magGain20) && (lhs.magGain21 == rhs.magGain21) &&
            (lhs.magGain22 == rhs.magGain22) && (lhs.magBiasX == rhs.magBiasX) && (lhs.magBiasY == rhs.magBiasY) && (lhs.magBiasZ == rhs.magBiasZ));
}

inline bool operator!=(const MagCal& lhs, const MagCal& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 25 - Accel Calibration </summary>
<remarks>
</remarks>
*-----------------------------------------------------------------------------------------------**/
class AccelCal : public ConfigurationRegister
{
public:
    std::optional<float> accelGain00;
    std::optional<float> accelGain01;
    std::optional<float> accelGain02;
    std::optional<float> accelGain10;
    std::optional<float> accelGain11;
    std::optional<float> accelGain12;
    std::optional<float> accelGain20;
    std::optional<float> accelGain21;
    std::optional<float> accelGain22;
    std::optional<float> accelBiasX;
    std::optional<float> accelBiasY;
    std::optional<float> accelBiasZ;

    AccelCal() : ConfigurationRegister(25) {}
    static constexpr const char* name() { return "AccelCal"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    AsciiMessage toString() const override;
};

inline bool operator==(const AccelCal& lhs, const AccelCal& rhs)
{
    return ((lhs.accelGain00 == rhs.accelGain00) && (lhs.accelGain01 == rhs.accelGain01) && (lhs.accelGain02 == rhs.accelGain02) &&
            (lhs.accelGain10 == rhs.accelGain10) && (lhs.accelGain11 == rhs.accelGain11) && (lhs.accelGain12 == rhs.accelGain12) &&
            (lhs.accelGain20 == rhs.accelGain20) && (lhs.accelGain21 == rhs.accelGain21) && (lhs.accelGain22 == rhs.accelGain22) &&
            (lhs.accelBiasX == rhs.accelBiasX) && (lhs.accelBiasY == rhs.accelBiasY) && (lhs.accelBiasZ == rhs.accelBiasZ));
}

inline bool operator!=(const AccelCal& lhs, const AccelCal& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 26 - Reference Frame Rotation </summary>
<remarks>
</remarks>
*-----------------------------------------------------------------------------------------------**/
class RefFrameRot : public ConfigurationRegister
{
public:
    std::optional<float> rfr00;
    std::optional<float> rfr01;
    std::optional<float> rfr02;
    std::optional<float> rfr10;
    std::optional<float> rfr11;
    std::optional<float> rfr12;
    std::optional<float> rfr20;
    std::optional<float> rfr21;
    std::optional<float> rfr22;

    RefFrameRot() : ConfigurationRegister(26) {}
    static constexpr const char* name() { return "RefFrameRot"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    AsciiMessage toString() const override;
};

inline bool operator==(const RefFrameRot& lhs, const RefFrameRot& rhs)
{
    return ((lhs.rfr00 == rhs.rfr00) && (lhs.rfr01 == rhs.rfr01) && (lhs.rfr02 == rhs.rfr02) && (lhs.rfr10 == rhs.rfr10) && (lhs.rfr11 == rhs.rfr11) &&
            (lhs.rfr12 == rhs.rfr12) && (lhs.rfr20 == rhs.rfr20) && (lhs.rfr21 == rhs.rfr21) && (lhs.rfr22 == rhs.rfr22));
}

inline bool operator!=(const RefFrameRot& lhs, const RefFrameRot& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 54 - IMU Measurements </summary>
<remarks>

Provides the calibrated IMU measurements including barometric pressure.

</remarks>
*-----------------------------------------------------------------------------------------------**/
class ImuMeas : public MeasurementRegister
{
public:
    float uncompMagX = 0;   ///< Magnetometer body-frame x-axis.
    float uncompMagY = 0;   ///< Magnetometer body-frame y-axis.
    float uncompMagZ = 0;   ///< Magnetometer body-frame z-axis.
    float uncompAccX = 0;   ///< Accelerometer body-frame x-axis.
    float uncompAccY = 0;   ///< Accelerometer body-frame y-axis.
    float uncompAccZ = 0;   ///< Accelerometer body-frame z-axis.
    float uncompGyroX = 0;  ///< Angular rate body-frame x-axis.
    float uncompGyroY = 0;  ///< Angular rate body-frame y-axis.
    float uncompGyroZ = 0;  ///< Angular rate body-frame z-axis.
    float temperature = 0;  ///< Sensor temperature.
    float pressure = 0;     ///< Barometric pressure.

    ImuMeas() : MeasurementRegister(54) {}
    static constexpr const char* name() { return "ImuMeas"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    using MeasurementRegister::toString;
};

inline bool operator==(const ImuMeas& lhs, const ImuMeas& rhs)
{
    return ((lhs.uncompMagX == rhs.uncompMagX) && (lhs.uncompMagY == rhs.uncompMagY) && (lhs.uncompMagZ == rhs.uncompMagZ) &&
            (lhs.uncompAccX == rhs.uncompAccX) && (lhs.uncompAccY == rhs.uncompAccY) && (lhs.uncompAccZ == rhs.uncompAccZ) &&
            (lhs.uncompGyroX == rhs.uncompGyroX) && (lhs.uncompGyroY == rhs.uncompGyroY) && (lhs.uncompGyroZ == rhs.uncompGyroZ) &&
            (lhs.temperature == rhs.temperature) && (lhs.pressure == rhs.pressure));
}

inline bool operator!=(const ImuMeas& lhs, const ImuMeas& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 80 - Delta Theta and Delta Velocity </summary>
<remarks>

This register contains the output values of the onboard coning and sculling algorithm.

</remarks>
*-----------------------------------------------------------------------------------------------**/
class DeltaThetaVelocity : public MeasurementRegister
{
public:
    float deltaTime = 0;    ///< Duration of integration interval.
    float deltaThetaX = 0;  ///< Integrated rotation vector x-axis.
    float deltaThetaY = 0;  ///< Integrated rotation vector y-axis.
    float deltaThetaZ = 0;  ///< Integrated rotation vector z-axis.
    float deltaVelX = 0;    ///< Integrated velocity x-axis.
    float deltaVelY = 0;    ///< Integrated velocity y-axis.
    float deltaVelZ = 0;    ///< Integrated velocity z-axis.

    DeltaThetaVelocity() : MeasurementRegister(80) {}
    static constexpr const char* name() { return "DeltaThetaVelocity"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    using MeasurementRegister::toString;
};

inline bool operator==(const DeltaThetaVelocity& lhs, const DeltaThetaVelocity& rhs)
{
    return ((lhs.deltaTime == rhs.deltaTime) && (lhs.deltaThetaX == rhs.deltaThetaX) && (lhs.deltaThetaY == rhs.deltaThetaY) &&
            (lhs.deltaThetaZ == rhs.deltaThetaZ) && (lhs.deltaVelX == rhs.deltaVelX) && (lhs.deltaVelY == rhs.deltaVelY) && (lhs.deltaVelZ == rhs.deltaVelZ));
}

inline bool operator!=(const DeltaThetaVelocity& lhs, const DeltaThetaVelocity& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 82 - Delta Theta and Delta Velocity Configuration </summary>
<remarks>
</remarks>
*-----------------------------------------------------------------------------------------------**/
class DeltaThetaVelConfig : public ConfigurationRegister
{
public:
    enum class IntegrationFrame : uint8_t
    {
        Body = 0,
        NED = 1,
    };

    enum class GyroCompensation : uint8_t
    {
        None = 0,
        Bias = 1,
    };

    enum class AccelCompensation : uint8_t
    {
        None = 0,
        Gravity = 1,
        Bias = 2,
        BiasAndGravity = 3,
    };

    enum class EarthRateCompensation : uint8_t
    {
        None = 0,
        GyroRate = 1,
        CoriolisAccel = 2,
        RateAndCoriolis = 3,
    };

    std::optional<IntegrationFrame> integrationFrame;
    std::optional<GyroCompensation> gyroCompensation;
    std::optional<AccelCompensation> accelCompensation;
    std::optional<EarthRateCompensation> earthRateCompensation;
    std::optional<uint16_t> resv;

    DeltaThetaVelConfig() : ConfigurationRegister(82) {}
    static constexpr const char* name() { return "DeltaThetaVelConfig"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    AsciiMessage toString() const override;
};

inline bool operator==(const DeltaThetaVelConfig& lhs, const DeltaThetaVelConfig& rhs)
{
    return ((lhs.integrationFrame == rhs.integrationFrame) && (lhs.gyroCompensation == rhs.gyroCompensation) &&
            (lhs.accelCompensation == rhs.accelCompensation) && (lhs.earthRateCompensation == rhs.earthRateCompensation) && (lhs.resv == rhs.resv));
}

inline bool operator!=(const DeltaThetaVelConfig& lhs, const DeltaThetaVelConfig& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 84 - Gyro Calibration </summary>
<remarks>
</remarks>
*-----------------------------------------------------------------------------------------------**/
class GyroCal : public ConfigurationRegister
{
public:
    std::optional<float> gyroGain00;
    std::optional<float> gyroGain01;
    std::optional<float> gyroGain02;
    std::optional<float> gyroGain10;
    std::optional<float> gyroGain11;
    std::optional<float> gyroGain12;
    std::optional<float> gyroGain20;
    std::optional<float> gyroGain21;
    std::optional<float> gyroGain22;
    std::optional<float> gyroBiasX;
    std::optional<float> gyroBiasY;
    std::optional<float> gyroBiasZ;

    GyroCal() : ConfigurationRegister(84) {}
    static constexpr const char* name() { return "GyroCal"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    AsciiMessage toString() const override;
};

inline bool operator==(const GyroCal& lhs, const GyroCal& rhs)
{
    return ((lhs.gyroGain00 == rhs.gyroGain00) && (lhs.gyroGain01 == rhs.gyroGain01) && (lhs.gyroGain02 == rhs.gyroGain02) &&
            (lhs.gyroGain10 == rhs.gyroGain10) && (lhs.gyroGain11 == rhs.gyroGain11) && (lhs.gyroGain12 == rhs.gyroGain12) &&
            (lhs.gyroGain20 == rhs.gyroGain20) && (lhs.gyroGain21 == rhs.gyroGain21) && (lhs.gyroGain22 == rhs.gyroGain22) &&
            (lhs.gyroBiasX == rhs.gyroBiasX) && (lhs.gyroBiasY == rhs.gyroBiasY) && (lhs.gyroBiasZ == rhs.gyroBiasZ));
}

inline bool operator!=(const GyroCal& lhs, const GyroCal& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 85 - IMU Filtering Configuration </summary>
<remarks>
</remarks>
*-----------------------------------------------------------------------------------------------**/
class ImuFilterControl : public ConfigurationRegister
{
public:
    struct MagFilterMode
    {
        uint8_t uncomp : 1;
        uint8_t comp : 1;
        uint8_t : 6;  // padding

        MagFilterMode() noexcept : MagFilterMode(0) {}
        MagFilterMode(uint8_t in) noexcept { std::memcpy(this, &in, sizeof(MagFilterMode)); }

        explicit operator uint8_t() const
        {
            uint8_t result;
            std::memcpy(&result, this, sizeof(MagFilterMode));
            return result;
        }

        MagFilterMode& operator=(const uint8_t& other)
        {
            std::memcpy(this, &other, sizeof(MagFilterMode));
            return *this;
        }
    };
    static_assert(sizeof(MagFilterMode) == 1);

    struct AccelFilterMode
    {
        uint8_t uncomp : 1;
        uint8_t comp : 1;
        uint8_t : 6;  // padding

        AccelFilterMode() noexcept : AccelFilterMode(0) {}
        AccelFilterMode(uint8_t in) noexcept { std::memcpy(this, &in, sizeof(AccelFilterMode)); }

        explicit operator uint8_t() const
        {
            uint8_t result;
            std::memcpy(&result, this, sizeof(AccelFilterMode));
            return result;
        }

        AccelFilterMode& operator=(const uint8_t& other)
        {
            std::memcpy(this, &other, sizeof(AccelFilterMode));
            return *this;
        }
    };
    static_assert(sizeof(AccelFilterMode) == 1);

    struct GyroFilterMode
    {
        uint8_t uncomp : 1;
        uint8_t comp : 1;
        uint8_t : 6;  // padding

        GyroFilterMode() noexcept : GyroFilterMode(0) {}
        GyroFilterMode(uint8_t in) noexcept { std::memcpy(this, &in, sizeof(GyroFilterMode)); }

        explicit operator uint8_t() const
        {
            uint8_t result;
            std::memcpy(&result, this, sizeof(GyroFilterMode));
            return result;
        }

        GyroFilterMode& operator=(const uint8_t& other)
        {
            std::memcpy(this, &other, sizeof(GyroFilterMode));
            return *this;
        }
    };
    static_assert(sizeof(GyroFilterMode) == 1);

    struct TempFilterMode
    {
        uint8_t uncomp : 1;
        uint8_t comp : 1;
        uint8_t : 6;  // padding

        TempFilterMode() noexcept : TempFilterMode(0) {}
        TempFilterMode(uint8_t in) noexcept { std::memcpy(this, &in, sizeof(TempFilterMode)); }

        explicit operator uint8_t() const
        {
            uint8_t result;
            std::memcpy(&result, this, sizeof(TempFilterMode));
            return result;
        }

        TempFilterMode& operator=(const uint8_t& other)
        {
            std::memcpy(this, &other, sizeof(TempFilterMode));
            return *this;
        }
    };
    static_assert(sizeof(TempFilterMode) == 1);

    struct PresFilterMode
    {
        uint8_t uncomp : 1;
        uint8_t comp : 1;
        uint8_t : 6;  // padding

        PresFilterMode() noexcept : PresFilterMode(0) {}
        PresFilterMode(uint8_t in) noexcept { std::memcpy(this, &in, sizeof(PresFilterMode)); }

        explicit operator uint8_t() const
        {
            uint8_t result;
            std::memcpy(&result, this, sizeof(PresFilterMode));
            return result;
        }

        PresFilterMode& operator=(const uint8_t& other)
        {
            std::memcpy(this, &other, sizeof(PresFilterMode));
            return *this;
        }
    };
    static_assert(sizeof(PresFilterMode) == 1);

    std::optional<uint16_t> magWindowSize;
    std::optional<uint16_t> accelWindowSize;
    std::optional<uint16_t> gyroWindowSize;
    std::optional<uint16_t> tempWindowSize;
    std::optional<uint16_t> presWindowSize;
    std::optional<MagFilterMode> magFilterMode;
    std::optional<AccelFilterMode> accelFilterMode;
    std::optional<GyroFilterMode> gyroFilterMode;
    std::optional<TempFilterMode> tempFilterMode;
    std::optional<PresFilterMode> presFilterMode;

    ImuFilterControl() : ConfigurationRegister(85) {}
    static constexpr const char* name() { return "ImuFilterControl"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    AsciiMessage toString() const override;
};

inline bool operator==(const ImuFilterControl::MagFilterMode& lhs, const ImuFilterControl::MagFilterMode& rhs) noexcept
{
    return static_cast<uint8_t>(lhs) == static_cast<uint8_t>(rhs);
}
inline bool operator!=(const ImuFilterControl::MagFilterMode& lhs, const ImuFilterControl::MagFilterMode& rhs) noexcept { return !(lhs == rhs); }

inline bool operator==(const ImuFilterControl::AccelFilterMode& lhs, const ImuFilterControl::AccelFilterMode& rhs) noexcept
{
    return static_cast<uint8_t>(lhs) == static_cast<uint8_t>(rhs);
}
inline bool operator!=(const ImuFilterControl::AccelFilterMode& lhs, const ImuFilterControl::AccelFilterMode& rhs) noexcept { return !(lhs == rhs); }

inline bool operator==(const ImuFilterControl::GyroFilterMode& lhs, const ImuFilterControl::GyroFilterMode& rhs) noexcept
{
    return static_cast<uint8_t>(lhs) == static_cast<uint8_t>(rhs);
}
inline bool operator!=(const ImuFilterControl::GyroFilterMode& lhs, const ImuFilterControl::GyroFilterMode& rhs) noexcept { return !(lhs == rhs); }

inline bool operator==(const ImuFilterControl::TempFilterMode& lhs, const ImuFilterControl::TempFilterMode& rhs) noexcept
{
    return static_cast<uint8_t>(lhs) == static_cast<uint8_t>(rhs);
}
inline bool operator!=(const ImuFilterControl::TempFilterMode& lhs, const ImuFilterControl::TempFilterMode& rhs) noexcept { return !(lhs == rhs); }

inline bool operator==(const ImuFilterControl::PresFilterMode& lhs, const ImuFilterControl::PresFilterMode& rhs) noexcept
{
    return static_cast<uint8_t>(lhs) == static_cast<uint8_t>(rhs);
}
inline bool operator!=(const ImuFilterControl::PresFilterMode& lhs, const ImuFilterControl::PresFilterMode& rhs) noexcept { return !(lhs == rhs); }

inline bool operator==(const ImuFilterControl& lhs, const ImuFilterControl& rhs)
{
    return ((lhs.magWindowSize == rhs.magWindowSize) && (lhs.accelWindowSize == rhs.accelWindowSize) && (lhs.gyroWindowSize == rhs.gyroWindowSize) &&
            (lhs.tempWindowSize == rhs.tempWindowSize) && (lhs.presWindowSize == rhs.presWindowSize) && (lhs.magFilterMode == rhs.magFilterMode) &&
            (lhs.accelFilterMode == rhs.accelFilterMode) && (lhs.gyroFilterMode == rhs.gyroFilterMode) && (lhs.tempFilterMode == rhs.tempFilterMode) &&
            (lhs.presFilterMode == rhs.presFilterMode));
}

inline bool operator!=(const ImuFilterControl& lhs, const ImuFilterControl& rhs) { return !(lhs == rhs); }
}  // namespace IMU

namespace INS
{
/**--------------------------------------------------------------------------------------------------
<summary> Register 63 - INS Solution - LLA </summary>
<remarks>

Estimated INS solution with lat/lon/alt position.

</remarks>
*-----------------------------------------------------------------------------------------------**/
class InsSolLla : public MeasurementRegister
{
public:
    using InsStatus = VN::InsStatus;

    double timeGpsTow = 0;     ///< GPS time of week.
    uint16_t timeGpsWeek = 0;  ///< The current GPS week.
    InsStatus insStatus = 0;   ///< Ins status bitfield.
    float yaw = 0;             ///< Yaw angle.
    float pitch = 0;           ///< Pitch angle.
    float roll = 0;            ///< Roll angle.
    double posLat = 0;         ///< Geodetic latitude.
    double posLon = 0;         ///< Longitude.
    double posAlt = 0;         ///< Altitude above WGS84 ellipsoid.
    float velN = 0;            ///< Velocity in North direction.
    float velE = 0;            ///< Velocity in East direction.
    float velD = 0;            ///< Velocity in Down direction.
    float attUncertainty = 0;  ///< Filter estimated attitude uncertainty.
    float posUncertainty = 0;  ///< Filter estimated position uncertainty.
    float velUncertainty = 0;  ///< Filter estimated velocity uncertainty.

    InsSolLla() : MeasurementRegister(63) {}
    static constexpr const char* name() { return "InsSolLla"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    using MeasurementRegister::toString;
};

inline bool operator==(const InsSolLla& lhs, const InsSolLla& rhs)
{
    return ((lhs.timeGpsTow == rhs.timeGpsTow) && (lhs.timeGpsWeek == rhs.timeGpsWeek) && (lhs.insStatus == rhs.insStatus) && (lhs.yaw == rhs.yaw) &&
            (lhs.pitch == rhs.pitch) && (lhs.roll == rhs.roll) && (lhs.posLat == rhs.posLat) && (lhs.posLon == rhs.posLon) && (lhs.posAlt == rhs.posAlt) &&
            (lhs.velN == rhs.velN) && (lhs.velE == rhs.velE) && (lhs.velD == rhs.velD) && (lhs.attUncertainty == rhs.attUncertainty) &&
            (lhs.posUncertainty == rhs.posUncertainty) && (lhs.velUncertainty == rhs.velUncertainty));
}

inline bool operator!=(const InsSolLla& lhs, const InsSolLla& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 64 - INS Solution - ECEF </summary>
<remarks>

Estimated INS Solution with ECEF position

</remarks>
*-----------------------------------------------------------------------------------------------**/
class InsSolEcef : public MeasurementRegister
{
public:
    using InsStatus = VN::InsStatus;

    double timeGpsTow = 0;     ///< GPS time of week.
    uint16_t timeGpsWeek = 0;  ///< The current GPS week.
    InsStatus insStatus = 0;   ///< Ins status bitfield.
    float yaw = 0;             ///< Yaw angle.
    float pitch = 0;           ///< Pitch angle.
    float roll = 0;            ///< Roll angle.
    double posEx = 0;          ///< Position in ECEF-frame x-axis.
    double posEy = 0;          ///< Position in ECEF-frame y-axis.
    double posEz = 0;          ///< Position in ECEF-frame z-axis.
    float velEx = 0;           ///< Velocity in ECEF-frame x-axis.
    float velEy = 0;           ///< Velocity in ECEF-frame y-axis.
    float velEz = 0;           ///< Velocity in ECEF-frame z-axis.
    float attUncertainty = 0;  ///< Filter estimated attitude uncertainty.
    float posUncertainty = 0;  ///< Filter estimated position uncertainty.
    float velUncertainty = 0;  ///< Filter estimated velocity uncertainty.

    InsSolEcef() : MeasurementRegister(64) {}
    static constexpr const char* name() { return "InsSolEcef"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    using MeasurementRegister::toString;
};

inline bool operator==(const InsSolEcef& lhs, const InsSolEcef& rhs)
{
    return ((lhs.timeGpsTow == rhs.timeGpsTow) && (lhs.timeGpsWeek == rhs.timeGpsWeek) && (lhs.insStatus == rhs.insStatus) && (lhs.yaw == rhs.yaw) &&
            (lhs.pitch == rhs.pitch) && (lhs.roll == rhs.roll) && (lhs.posEx == rhs.posEx) && (lhs.posEy == rhs.posEy) && (lhs.posEz == rhs.posEz) &&
            (lhs.velEx == rhs.velEx) && (lhs.velEy == rhs.velEy) && (lhs.velEz == rhs.velEz) && (lhs.attUncertainty == rhs.attUncertainty) &&
            (lhs.posUncertainty == rhs.posUncertainty) && (lhs.velUncertainty == rhs.velUncertainty));
}

inline bool operator!=(const InsSolEcef& lhs, const InsSolEcef& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 67 - INS Basic Configuration </summary>
<remarks>
</remarks>
*-----------------------------------------------------------------------------------------------**/
class InsBasicConfig : public ConfigurationRegister
{
public:
    enum class Scenario : uint8_t
    {
        Ahrs = 0,
        GnssInsWithPressure = 1,
        GnssInsNoPressure = 2,
        DualGnssNoPressure = 3,
        DualGnssWithPressure = 5,
    };

    enum class AhrsAiding : uint8_t
    {
        Disable = 0,
        Enable = 1,
    };

    enum class EstBaseline : uint8_t
    {
        Disable = 0,
        Enable = 1,
    };

    std::optional<Scenario> scenario;
    std::optional<AhrsAiding> ahrsAiding;
    std::optional<EstBaseline> estBaseline;
    std::optional<uint8_t> resv;

    InsBasicConfig() : ConfigurationRegister(67) {}
    static constexpr const char* name() { return "InsBasicConfig"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    AsciiMessage toString() const override;
};

inline bool operator==(const InsBasicConfig& lhs, const InsBasicConfig& rhs)
{
    return ((lhs.scenario == rhs.scenario) && (lhs.ahrsAiding == rhs.ahrsAiding) && (lhs.estBaseline == rhs.estBaseline) && (lhs.resv == rhs.resv));
}

inline bool operator!=(const InsBasicConfig& lhs, const InsBasicConfig& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 72 - INS State - LLA </summary>
<remarks>

Estimated INS state with lat/lon/alt position.

</remarks>
*-----------------------------------------------------------------------------------------------**/
class InsStateLla : public MeasurementRegister
{
public:
    float yaw = 0;      ///< Yaw angle.
    float pitch = 0;    ///< Pitch angle.
    float roll = 0;     ///< Roll angle.
    double posLat = 0;  ///< Geodetic latitude.
    double posLon = 0;  ///< Longitude.
    double posAlt = 0;  ///< Altitude above WGS84 ellipsoid.
    float velN = 0;     ///< Velocity in North direction.
    float velE = 0;     ///< Velocity in East direction.
    float velD = 0;     ///< Velocity in Down direction.
    float accelX = 0;   ///< Compensated accelerometer measurement in the body-frame x-axis.
    float accelY = 0;   ///< Compensated accelerometer measurement in the body-frame y-axis.
    float accelZ = 0;   ///< Compensated accelerometer measurement in the body-frame z-axis.
    float gyroX = 0;    ///< Compensated angular rate measurement in the body-frame x-axis.
    float gyroY = 0;    ///< Compensated angular rate measurement in the body-frame y-axis.
    float gyroZ = 0;    ///< Compensated angular rate measurement in the body-frame z-axis.

    InsStateLla() : MeasurementRegister(72) {}
    static constexpr const char* name() { return "InsStateLla"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    using MeasurementRegister::toString;
};

inline bool operator==(const InsStateLla& lhs, const InsStateLla& rhs)
{
    return ((lhs.yaw == rhs.yaw) && (lhs.pitch == rhs.pitch) && (lhs.roll == rhs.roll) && (lhs.posLat == rhs.posLat) && (lhs.posLon == rhs.posLon) &&
            (lhs.posAlt == rhs.posAlt) && (lhs.velN == rhs.velN) && (lhs.velE == rhs.velE) && (lhs.velD == rhs.velD) && (lhs.accelX == rhs.accelX) &&
            (lhs.accelY == rhs.accelY) && (lhs.accelZ == rhs.accelZ) && (lhs.gyroX == rhs.gyroX) && (lhs.gyroY == rhs.gyroY) && (lhs.gyroZ == rhs.gyroZ));
}

inline bool operator!=(const InsStateLla& lhs, const InsStateLla& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 73 - INS State - ECEF </summary>
<remarks>

Estimated INS state with ECEF position.

</remarks>
*-----------------------------------------------------------------------------------------------**/
class InsStateEcef : public MeasurementRegister
{
public:
    float yaw = 0;     ///< Yaw angle.
    float pitch = 0;   ///< Pitch angle.
    float roll = 0;    ///< Roll angle.
    double posEx = 0;  ///< Position in ECEF-frame x-axis.
    double posEy = 0;  ///< Position in ECEF-frame y-axis.
    double posEz = 0;  ///< Position in ECEF-frame z-axis.
    float velEx = 0;   ///< Velocity in ECEF-frame x-axis.
    float velEy = 0;   ///< Velocity in ECEF-frame y-axis.
    float velEz = 0;   ///< Velocity in ECEF-frame z-axis.
    float accelX = 0;  ///< Compensated accelerometer measurement in the body-frame x-axis.
    float accelY = 0;  ///< Compensated accelerometer measurement in the body-frame y-axis.
    float accelZ = 0;  ///< Compensated accelerometer measurement in the body-frame z-axis.
    float gyroX = 0;   ///< Compensated angular rate measurement in the body-frame x-axis.
    float gyroY = 0;   ///< Compensated angular rate measurement in the body-frame y-axis.
    float gyroZ = 0;   ///< Compensated angular rate measurement in the body-frame z-axis.

    InsStateEcef() : MeasurementRegister(73) {}
    static constexpr const char* name() { return "InsStateEcef"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    using MeasurementRegister::toString;
};

inline bool operator==(const InsStateEcef& lhs, const InsStateEcef& rhs)
{
    return ((lhs.yaw == rhs.yaw) && (lhs.pitch == rhs.pitch) && (lhs.roll == rhs.roll) && (lhs.posEx == rhs.posEx) && (lhs.posEy == rhs.posEy) &&
            (lhs.posEz == rhs.posEz) && (lhs.velEx == rhs.velEx) && (lhs.velEy == rhs.velEy) && (lhs.velEz == rhs.velEz) && (lhs.accelX == rhs.accelX) &&
            (lhs.accelY == rhs.accelY) && (lhs.accelZ == rhs.accelZ) && (lhs.gyroX == rhs.gyroX) && (lhs.gyroY == rhs.gyroY) && (lhs.gyroZ == rhs.gyroZ));
}

inline bool operator!=(const InsStateEcef& lhs, const InsStateEcef& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 74 - Filter Startup Bias </summary>
<remarks>
</remarks>
*-----------------------------------------------------------------------------------------------**/
class FilterStartupBias : public ConfigurationRegister
{
public:
    std::optional<float> gyroBiasX;
    std::optional<float> gyroBiasY;
    std::optional<float> gyroBiasZ;
    std::optional<float> accelBiasX;
    std::optional<float> accelBiasY;
    std::optional<float> accelBiasZ;
    std::optional<float> presBias;

    FilterStartupBias() : ConfigurationRegister(74) {}
    static constexpr const char* name() { return "FilterStartupBias"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    AsciiMessage toString() const override;
};

inline bool operator==(const FilterStartupBias& lhs, const FilterStartupBias& rhs)
{
    return ((lhs.gyroBiasX == rhs.gyroBiasX) && (lhs.gyroBiasY == rhs.gyroBiasY) && (lhs.gyroBiasZ == rhs.gyroBiasZ) && (lhs.accelBiasX == rhs.accelBiasX) &&
            (lhs.accelBiasY == rhs.accelBiasY) && (lhs.accelBiasZ == rhs.accelBiasZ) && (lhs.presBias == rhs.presBias));
}

inline bool operator!=(const FilterStartupBias& lhs, const FilterStartupBias& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 105 - INS Reference Point Offset </summary>
<remarks>
</remarks>
*-----------------------------------------------------------------------------------------------**/
class InsRefOffset : public ConfigurationRegister
{
public:
    std::optional<float> refOffsetX;
    std::optional<float> refOffsetY;
    std::optional<float> refOffsetZ;
    std::optional<float> refUncertX;
    std::optional<float> refUncertY;
    std::optional<float> refUncertZ;

    InsRefOffset() : ConfigurationRegister(105) {}
    static constexpr const char* name() { return "InsRefOffset"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    AsciiMessage toString() const override;
};

inline bool operator==(const InsRefOffset& lhs, const InsRefOffset& rhs)
{
    return ((lhs.refOffsetX == rhs.refOffsetX) && (lhs.refOffsetY == rhs.refOffsetY) && (lhs.refOffsetZ == rhs.refOffsetZ) &&
            (lhs.refUncertX == rhs.refUncertX) && (lhs.refUncertY == rhs.refUncertY) && (lhs.refUncertZ == rhs.refUncertZ));
}

inline bool operator!=(const InsRefOffset& lhs, const InsRefOffset& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 144 - INS GNSS Select </summary>
<remarks>
</remarks>
*-----------------------------------------------------------------------------------------------**/
class InsGnssSelect : public ConfigurationRegister
{
public:
    enum class ActiveReceiverSelect : uint8_t
    {
        None = 0,
        PrimaryReceiver = 1,
        SecondaryReceiver = 2,
        TertiaryReceiver = 3,
        FallbackOnFailure = 5,
    };

    enum class UseGnssCompass : uint8_t
    {
        Off = 0,
        On = 1,
    };

    std::optional<ActiveReceiverSelect> activeReceiverSelect;
    std::optional<uint8_t> usedForNavTime;
    std::optional<uint8_t> hysteresisTime;
    std::optional<UseGnssCompass> useGnssCompass;
    std::optional<uint8_t> resv1;
    std::optional<uint8_t> resv2;

    InsGnssSelect() : ConfigurationRegister(144) {}
    static constexpr const char* name() { return "InsGnssSelect"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    AsciiMessage toString() const override;
};

inline bool operator==(const InsGnssSelect& lhs, const InsGnssSelect& rhs)
{
    return ((lhs.activeReceiverSelect == rhs.activeReceiverSelect) && (lhs.usedForNavTime == rhs.usedForNavTime) &&
            (lhs.hysteresisTime == rhs.hysteresisTime) && (lhs.useGnssCompass == rhs.useGnssCompass) && (lhs.resv1 == rhs.resv1) && (lhs.resv2 == rhs.resv2));
}

inline bool operator!=(const InsGnssSelect& lhs, const InsGnssSelect& rhs) { return !(lhs == rhs); }
}  // namespace INS

namespace System
{
/**--------------------------------------------------------------------------------------------------
<summary> Register 0 - User Tag </summary>
<remarks>
</remarks>
*-----------------------------------------------------------------------------------------------**/
class UserTag : public ConfigurationRegister
{
public:
    std::optional<AsciiMessage> tag;
    UserTag() : ConfigurationRegister(0) {}
    static constexpr const char* name() { return "UserTag"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    AsciiMessage toString() const override;
};

inline bool operator==(const UserTag& lhs, const UserTag& rhs) { return ((lhs.tag == rhs.tag)); }

inline bool operator!=(const UserTag& lhs, const UserTag& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 1 - Model </summary>
<remarks>

Product model string.

</remarks>
*-----------------------------------------------------------------------------------------------**/
class Model : public MeasurementRegister
{
public:
    AsciiMessage model = "";  ///< Product model number, maximum length 24 characters.

    Model() : MeasurementRegister(1) {}
    static constexpr const char* name() { return "Model"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    using MeasurementRegister::toString;
};

inline bool operator==(const Model& lhs, const Model& rhs) { return ((lhs.model == rhs.model)); }

inline bool operator!=(const Model& lhs, const Model& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 2 - Hardware Version </summary>
<remarks>

Hardware version number.

</remarks>
*-----------------------------------------------------------------------------------------------**/
class HwVer : public MeasurementRegister
{
public:
    uint32_t hwVer = 0;     ///< Hardware version number.
    uint32_t hwMinVer = 0;  ///< Hardware minor version number.

    HwVer() : MeasurementRegister(2) {}
    static constexpr const char* name() { return "HwVer"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    using MeasurementRegister::toString;
};

inline bool operator==(const HwVer& lhs, const HwVer& rhs) { return ((lhs.hwVer == rhs.hwVer) && (lhs.hwMinVer == rhs.hwMinVer)); }

inline bool operator!=(const HwVer& lhs, const HwVer& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 3 - Serial Number </summary>
<remarks>

Device serial number.

</remarks>
*-----------------------------------------------------------------------------------------------**/
class Serial : public MeasurementRegister
{
public:
    uint32_t serialNum = 0;  ///< The unit's serial number.

    Serial() : MeasurementRegister(3) {}
    static constexpr const char* name() { return "Serial"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    using MeasurementRegister::toString;
};

inline bool operator==(const Serial& lhs, const Serial& rhs) { return ((lhs.serialNum == rhs.serialNum)); }

inline bool operator!=(const Serial& lhs, const Serial& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 4 - Firmware Version </summary>
<remarks>

Firmware version number.

</remarks>
*-----------------------------------------------------------------------------------------------**/
class FwVer : public MeasurementRegister
{
public:
    AsciiMessage fwVer = "";  ///< Firmware version.

    FwVer() : MeasurementRegister(4) {}
    static constexpr const char* name() { return "FwVer"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    using MeasurementRegister::toString;
};

inline bool operator==(const FwVer& lhs, const FwVer& rhs) { return ((lhs.fwVer == rhs.fwVer)); }

inline bool operator!=(const FwVer& lhs, const FwVer& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 5 - Baud Rate </summary>
<remarks>
</remarks>
*-----------------------------------------------------------------------------------------------**/
class BaudRate : public ConfigurationRegister
{
public:
    enum class BaudRates : uint32_t
    {
        Baud9600 = 9600,
        Baud19200 = 19200,
        Baud38400 = 38400,
        Baud57600 = 57600,
        Baud115200 = 115200,
        Baud128000 = 128000,
        Baud230400 = 230400,
        Baud460800 = 460800,
        Baud921600 = 921600,
    };

    enum class SerialPort : uint8_t
    {
        ActiveSerial = 0,  ///< Set value on active serial port.
        Serial1 = 1,
        Serial2 = 2,
        Poll = static_cast<uint8_t>('?')
    };

    std::optional<BaudRates> baudRate;
    SerialPort serialPort{0};

    BaudRate() : ConfigurationRegister(5) {}
    static constexpr const char* name() { return "BaudRate"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    AsciiMessage toString() const override;
    GenericCommand toReadCommand() override;
};

inline bool operator==(const BaudRate& lhs, const BaudRate& rhs) { return ((lhs.baudRate == rhs.baudRate) && (lhs.serialPort == rhs.serialPort)); }

inline bool operator!=(const BaudRate& lhs, const BaudRate& rhs) { return !(lhs == rhs); }

inline std::ostream& operator<<(std::ostream& outStream, const BaudRate::BaudRates& baudrate) noexcept { return outStream << static_cast<uint32_t>(baudrate); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 6 - Async Data Output Type </summary>
<remarks>
</remarks>
*-----------------------------------------------------------------------------------------------**/
class AsyncOutputType : public ConfigurationRegister
{
public:
    enum class Ador : uint32_t
    {
        OFF = 0,
        YPR = 1,
        QTN = 2,
        QMR = 8,
        MAG = 10,
        ACC = 11,
        GYR = 12,
        MAR = 13,
        YMR = 14,
        YBA = 16,
        YIA = 17,
        IMU = 19,
        GPS = 20,
        GPE = 21,
        INS = 22,
        INE = 23,
        ISL = 28,
        ISE = 29,
        DTV = 30,
        G2S = 32,
        G2E = 33,
        HVE = 34,
    };

    enum class SerialPort : uint8_t
    {
        ActiveSerial = 0,  ///< Set value on active serial port.
        Serial1 = 1,
        Serial2 = 2,
        Poll = static_cast<uint8_t>('?')
    };

    std::optional<Ador> ador;
    SerialPort serialPort{0};

    AsyncOutputType() : ConfigurationRegister(6) {}
    static constexpr const char* name() { return "AsyncOutputType"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    AsciiMessage toString() const override;
    GenericCommand toReadCommand() override;
};

inline bool operator==(const AsyncOutputType& lhs, const AsyncOutputType& rhs) { return ((lhs.ador == rhs.ador) && (lhs.serialPort == rhs.serialPort)); }

inline bool operator!=(const AsyncOutputType& lhs, const AsyncOutputType& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 7 - Async Data Output Freq </summary>
<remarks>
</remarks>
*-----------------------------------------------------------------------------------------------**/
class AsyncOutputFreq : public ConfigurationRegister
{
public:
    enum class Adof : uint32_t
    {
        Rate0Hz = 0,
        Rate1Hz = 1,
        Rate2Hz = 2,
        Rate4Hz = 4,
        Rate5Hz = 5,
        Rate10Hz = 10,
        Rate20Hz = 20,
        Rate25Hz = 25,
        Rate40Hz = 40,
        Rate50Hz = 50,
        Rate100Hz = 100,
        Rate200Hz = 200,
    };

    enum class SerialPort : uint8_t
    {
        ActiveSerial = 0,  ///< Set value on active serial port.
        Serial1 = 1,
        Serial2 = 2,
        Poll = static_cast<uint8_t>('?')
    };

    std::optional<Adof> adof;
    SerialPort serialPort{0};

    AsyncOutputFreq() : ConfigurationRegister(7) {}
    static constexpr const char* name() { return "AsyncOutputFreq"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    AsciiMessage toString() const override;
    GenericCommand toReadCommand() override;
};

inline bool operator==(const AsyncOutputFreq& lhs, const AsyncOutputFreq& rhs) { return ((lhs.adof == rhs.adof) && (lhs.serialPort == rhs.serialPort)); }

inline bool operator!=(const AsyncOutputFreq& lhs, const AsyncOutputFreq& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 30 - Communication Protocol Control </summary>
<remarks>
</remarks>
*-----------------------------------------------------------------------------------------------**/
class ProtocolControl : public ConfigurationRegister
{
public:
    enum class AsciiAppendCount : uint8_t
    {
        None = 0,
        SyncInCount = 1,
        SyncInTime = 2,
        SyncOutCount = 3,
        GpsPps = 4,
        GpsTow = 5,
    };

    enum class AsciiAppendStatus : uint8_t
    {
        None = 0,
        Ahrs = 1,
        Ins = 2,
        Imu = 3,
        Gnss1 = 4,
        Gnss2 = 5,
        Gnss3 = 6,
    };

    enum class SpiAppendCount : uint8_t
    {
        None = 0,
        SyncInCount = 1,
        SyncInTime = 2,
        SyncOutCount = 3,
        GpsPps = 4,
        GpsTow = 5,
    };

    enum class SpiAppendStatus : uint8_t
    {
        None = 0,
        Ahrs = 1,
        Ins = 2,
        Imu = 3,
        Gnss1 = 4,
        Gnss2 = 5,
        Gnss3 = 6,
    };

    enum class AsciiChecksum : uint8_t
    {
        Checksum8bit = 1,
        Crc16bit = 3,
    };

    enum class SpiChecksum : uint8_t
    {
        Off = 0,
        Checksum8bit = 1,
        Crc16bit = 3,
    };

    enum class ErrorMode : uint8_t
    {
        Ignore = 0,
        SendError = 1,
        AdorOff = 2,
    };

    std::optional<AsciiAppendCount> asciiAppendCount;
    std::optional<AsciiAppendStatus> asciiAppendStatus;
    std::optional<SpiAppendCount> spiAppendCount;
    std::optional<SpiAppendStatus> spiAppendStatus;
    std::optional<AsciiChecksum> asciiChecksum;
    std::optional<SpiChecksum> spiChecksum;
    std::optional<ErrorMode> errorMode;

    ProtocolControl() : ConfigurationRegister(30) {}
    static constexpr const char* name() { return "ProtocolControl"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    AsciiMessage toString() const override;
};

inline bool operator==(const ProtocolControl& lhs, const ProtocolControl& rhs)
{
    return ((lhs.asciiAppendCount == rhs.asciiAppendCount) && (lhs.asciiAppendStatus == rhs.asciiAppendStatus) && (lhs.spiAppendCount == rhs.spiAppendCount) &&
            (lhs.spiAppendStatus == rhs.spiAppendStatus) && (lhs.asciiChecksum == rhs.asciiChecksum) && (lhs.spiChecksum == rhs.spiChecksum) &&
            (lhs.errorMode == rhs.errorMode));
}

inline bool operator!=(const ProtocolControl& lhs, const ProtocolControl& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 32 - Synchronization Control </summary>
<remarks>
</remarks>
*-----------------------------------------------------------------------------------------------**/
class SyncControl : public ConfigurationRegister
{
public:
    enum class SyncInMode : uint8_t
    {
        Disable = 0,
        Count = 3,
        ImuSample = 4,
        AsyncAll = 5,
        Async0 = 6,
    };

    enum class SyncInEdge : uint8_t
    {
        RisingEdge = 0,
        FallingEdge = 1,
    };

    enum class SyncOutMode : uint8_t
    {
        None = 0,
        ImuStart = 1,
        ImuReady = 2,
        NavReady = 3,
        GpsPps = 6,
    };

    enum class SyncOutPolarity : uint8_t
    {
        NegativePulse = 0,
        PositivePulse = 1,
    };

    std::optional<SyncInMode> syncInMode;
    std::optional<SyncInEdge> syncInEdge;
    std::optional<uint16_t> syncInSkipFactor;
    std::optional<uint32_t> resv1;
    std::optional<SyncOutMode> syncOutMode;
    std::optional<SyncOutPolarity> syncOutPolarity;
    std::optional<uint16_t> syncOutSkipFactor;
    std::optional<uint32_t> syncOutPulseWidth;
    std::optional<uint32_t> resv2;

    SyncControl() : ConfigurationRegister(32) {}
    static constexpr const char* name() { return "SyncControl"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    AsciiMessage toString() const override;
};

inline bool operator==(const SyncControl& lhs, const SyncControl& rhs)
{
    return ((lhs.syncInMode == rhs.syncInMode) && (lhs.syncInEdge == rhs.syncInEdge) && (lhs.syncInSkipFactor == rhs.syncInSkipFactor) &&
            (lhs.resv1 == rhs.resv1) && (lhs.syncOutMode == rhs.syncOutMode) && (lhs.syncOutPolarity == rhs.syncOutPolarity) &&
            (lhs.syncOutSkipFactor == rhs.syncOutSkipFactor) && (lhs.syncOutPulseWidth == rhs.syncOutPulseWidth) && (lhs.resv2 == rhs.resv2));
}

inline bool operator!=(const SyncControl& lhs, const SyncControl& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 33 - Synchronization Status </summary>
<remarks>

Contains counters based on the SyncIn and SyncOut events.

</remarks>
*-----------------------------------------------------------------------------------------------**/
class SyncStatus : public MeasurementRegister
{
public:
    uint32_t syncInCount = 0;   ///< Amount of SyncIn Events that have occurred.
    uint32_t syncInTime = 0;    ///< The amount of time that has elapsed since the last SyncIn Event.
    uint32_t syncOutCount = 0;  ///< Keeps track of the number of times that a SyncOut pulse has occurred.

    SyncStatus() : MeasurementRegister(33) {}
    static constexpr const char* name() { return "SyncStatus"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    using MeasurementRegister::toString;
};

inline bool operator==(const SyncStatus& lhs, const SyncStatus& rhs)
{
    return ((lhs.syncInCount == rhs.syncInCount) && (lhs.syncInTime == rhs.syncInTime) && (lhs.syncOutCount == rhs.syncOutCount));
}

inline bool operator!=(const SyncStatus& lhs, const SyncStatus& rhs) { return !(lhs == rhs); }
struct BinaryOutputMeasurements
{
    struct Common
    {
        uint32_t timeStartup : 1;
        uint32_t timeGps : 1;
        uint32_t timeSyncIn : 1;
        uint32_t ypr : 1;
        uint32_t quaternion : 1;
        uint32_t angularRate : 1;
        uint32_t posLla : 1;
        uint32_t velNed : 1;
        uint32_t accel : 1;
        uint32_t imu : 1;
        uint32_t magPres : 1;
        uint32_t deltas : 1;
        uint32_t insStatus : 1;
        uint32_t syncInCnt : 1;
        uint32_t timeGpsPps : 1;

        Common() noexcept : Common(0) {}
        Common(uint32_t in) noexcept { std::memcpy(this, &in, sizeof(Common)); }
        explicit operator uint32_t() const
        {
            uint32_t result;
            std::memcpy(&result, this, sizeof(Common));
            return result;
        }
        Common& operator=(const uint32_t& other)
        {
            std::memcpy(this, &other, sizeof(Common));
            return *this;
        }

        uint32_t : 17;  ///< padding
    };
    static_assert(sizeof(Common) == 4);

    struct Time
    {
        uint32_t timeStartup : 1;
        uint32_t timeGps : 1;
        uint32_t timeGpsTow : 1;
        uint32_t timeGpsWeek : 1;
        uint32_t timeSyncIn : 1;
        uint32_t timeGpsPps : 1;
        uint32_t timeUtc : 1;
        uint32_t syncInCnt : 1;
        uint32_t syncOutCnt : 1;
        uint32_t timeStatus : 1;

        Time() noexcept : Time(0) {}
        Time(uint32_t in) noexcept { std::memcpy(this, &in, sizeof(Time)); }
        explicit operator uint32_t() const
        {
            uint32_t result;
            std::memcpy(&result, this, sizeof(Time));
            return result;
        }
        Time& operator=(const uint32_t& other)
        {
            std::memcpy(this, &other, sizeof(Time));
            return *this;
        }

        uint32_t : 22;  ///< padding
    };
    static_assert(sizeof(Time) == 4);

    struct Imu
    {
        uint32_t imuStatus : 1;
        uint32_t uncompMag : 1;
        uint32_t uncompAccel : 1;
        uint32_t uncompGyro : 1;
        uint32_t temperature : 1;
        uint32_t pressure : 1;
        uint32_t deltaTheta : 1;
        uint32_t deltaVel : 1;
        uint32_t mag : 1;
        uint32_t accel : 1;
        uint32_t angularRate : 1;
        uint32_t sensSat : 1;

        Imu() noexcept : Imu(0) {}
        Imu(uint32_t in) noexcept { std::memcpy(this, &in, sizeof(Imu)); }
        explicit operator uint32_t() const
        {
            uint32_t result;
            std::memcpy(&result, this, sizeof(Imu));
            return result;
        }
        Imu& operator=(const uint32_t& other)
        {
            std::memcpy(this, &other, sizeof(Imu));
            return *this;
        }

        uint32_t : 20;  ///< padding
    };
    static_assert(sizeof(Imu) == 4);

    struct Gnss
    {
        uint32_t gnss1TimeUtc : 1;
        uint32_t gps1Tow : 1;
        uint32_t gps1Week : 1;
        uint32_t gnss1NumSats : 1;
        uint32_t gnss1Fix : 1;
        uint32_t gnss1PosLla : 1;
        uint32_t gnss1PosEcef : 1;
        uint32_t gnss1VelNed : 1;
        uint32_t gnss1VelEcef : 1;
        uint32_t gnss1PosUncertainty : 1;
        uint32_t gnss1VelUncertainty : 1;
        uint32_t gnss1TimeUncertainty : 1;
        uint32_t gnss1TimeInfo : 1;
        uint32_t gnss1Dop : 1;
        uint32_t gnss1SatInfo : 1;
        uint32_t : 1;  ///< 15: Extension Bit
        uint32_t gnss1RawMeas : 1;
        uint32_t gnss1Status : 1;
        uint32_t gnss1AltMsl : 1;

        Gnss() noexcept : Gnss(0) {}
        Gnss(uint32_t in) noexcept { std::memcpy(this, &in, sizeof(Gnss)); }
        explicit operator uint32_t() const
        {
            uint32_t result;
            std::memcpy(&result, this, sizeof(Gnss));
            return result;
        }
        Gnss& operator=(const uint32_t& other)
        {
            std::memcpy(this, &other, sizeof(Gnss));
            return *this;
        }

        uint32_t : 13;  ///< padding
    };
    static_assert(sizeof(Gnss) == 4);

    struct Attitude
    {
        uint32_t : 1;  ///< 0: padding
        uint32_t ypr : 1;
        uint32_t quaternion : 1;
        uint32_t dcm : 1;
        uint32_t magNed : 1;
        uint32_t accelNed : 1;
        uint32_t linBodyAcc : 1;
        uint32_t linAccelNed : 1;
        uint32_t yprU : 1;
        uint32_t : 1;  ///< 9: padding
        uint32_t : 1;  ///< 10: padding
        uint32_t : 1;  ///< 11: padding
        uint32_t heave : 1;
        uint32_t attU : 1;

        Attitude() noexcept : Attitude(0) {}
        Attitude(uint32_t in) noexcept { std::memcpy(this, &in, sizeof(Attitude)); }
        explicit operator uint32_t() const
        {
            uint32_t result;
            std::memcpy(&result, this, sizeof(Attitude));
            return result;
        }
        Attitude& operator=(const uint32_t& other)
        {
            std::memcpy(this, &other, sizeof(Attitude));
            return *this;
        }

        uint32_t : 18;  ///< padding
    };
    static_assert(sizeof(Attitude) == 4);

    struct Ins
    {
        uint32_t insStatus : 1;
        uint32_t posLla : 1;
        uint32_t posEcef : 1;
        uint32_t velBody : 1;
        uint32_t velNed : 1;
        uint32_t velEcef : 1;
        uint32_t magEcef : 1;
        uint32_t accelEcef : 1;
        uint32_t linAccelEcef : 1;
        uint32_t posU : 1;
        uint32_t velU : 1;

        Ins() noexcept : Ins(0) {}
        Ins(uint32_t in) noexcept { std::memcpy(this, &in, sizeof(Ins)); }
        explicit operator uint32_t() const
        {
            uint32_t result;
            std::memcpy(&result, this, sizeof(Ins));
            return result;
        }
        Ins& operator=(const uint32_t& other)
        {
            std::memcpy(this, &other, sizeof(Ins));
            return *this;
        }

        uint32_t : 21;  ///< padding
    };
    static_assert(sizeof(Ins) == 4);

    struct Gnss2
    {
        uint32_t gnss2TimeUtc : 1;
        uint32_t gps2Tow : 1;
        uint32_t gps2Week : 1;
        uint32_t gnss2NumSats : 1;
        uint32_t gnss2Fix : 1;
        uint32_t gnss2PosLla : 1;
        uint32_t gnss2PosEcef : 1;
        uint32_t gnss2VelNed : 1;
        uint32_t gnss2VelEcef : 1;
        uint32_t gnss2PosUncertainty : 1;
        uint32_t gnss2VelUncertainty : 1;
        uint32_t gnss2TimeUncertainty : 1;
        uint32_t gnss2TimeInfo : 1;
        uint32_t gnss2Dop : 1;
        uint32_t gnss2SatInfo : 1;
        uint32_t : 1;  ///< 15: Extension Bit
        uint32_t gnss2RawMeas : 1;
        uint32_t gnss2Status : 1;
        uint32_t gnss2AltMsl : 1;

        Gnss2() noexcept : Gnss2(0) {}
        Gnss2(uint32_t in) noexcept { std::memcpy(this, &in, sizeof(Gnss2)); }
        explicit operator uint32_t() const
        {
            uint32_t result;
            std::memcpy(&result, this, sizeof(Gnss2));
            return result;
        }
        Gnss2& operator=(const uint32_t& other)
        {
            std::memcpy(this, &other, sizeof(Gnss2));
            return *this;
        }

        uint32_t : 13;  ///< padding
    };
    static_assert(sizeof(Gnss2) == 4);

    struct Gnss3
    {
        uint32_t gnss3TimeUtc : 1;
        uint32_t gps3Tow : 1;
        uint32_t gps3Week : 1;
        uint32_t gnss3NumSats : 1;
        uint32_t gnss3Fix : 1;
        uint32_t gnss3PosLla : 1;
        uint32_t gnss3PosEcef : 1;
        uint32_t gnss3VelNed : 1;
        uint32_t gnss3VelEcef : 1;
        uint32_t gnss3PosUncertainty : 1;
        uint32_t gnss3VelUncertainty : 1;
        uint32_t gnss3TimeUncertainty : 1;
        uint32_t gnss3TimeInfo : 1;
        uint32_t gnss3Dop : 1;
        uint32_t gnss3SatInfo : 1;
        uint32_t : 1;  ///< 15: Extension Bit
        uint32_t gnss3RawMeas : 1;
        uint32_t gnss3Status : 1;
        uint32_t gnss3AltMsl : 1;

        Gnss3() noexcept : Gnss3(0) {}
        Gnss3(uint32_t in) noexcept { std::memcpy(this, &in, sizeof(Gnss3)); }
        explicit operator uint32_t() const
        {
            uint32_t result;
            std::memcpy(&result, this, sizeof(Gnss3));
            return result;
        }
        Gnss3& operator=(const uint32_t& other)
        {
            std::memcpy(this, &other, sizeof(Gnss3));
            return *this;
        }

        uint32_t : 13;  ///< padding
    };
    static_assert(sizeof(Gnss3) == 4);

    Common common{0};
    Time time{0};
    Imu imu{0};
    Gnss gnss{0};
    Attitude attitude{0};
    Ins ins{0};
    Gnss2 gnss2{0};
    Gnss3 gnss3{0};

    BinaryHeader toBinaryHeader() const noexcept;
    Vector<uint8_t, binaryHeaderMaxLength> toHeaderBytes() const noexcept;
};

inline bool operator==(const BinaryOutputMeasurements::Common& lhs, const BinaryOutputMeasurements::Common& rhs) noexcept
{
    return static_cast<uint32_t>(lhs) == static_cast<uint32_t>(rhs);
}
inline bool operator!=(const BinaryOutputMeasurements::Common& lhs, const BinaryOutputMeasurements::Common& rhs) noexcept { return !(lhs == rhs); }

inline bool operator==(const BinaryOutputMeasurements::Time& lhs, const BinaryOutputMeasurements::Time& rhs) noexcept
{
    return static_cast<uint32_t>(lhs) == static_cast<uint32_t>(rhs);
}
inline bool operator!=(const BinaryOutputMeasurements::Time& lhs, const BinaryOutputMeasurements::Time& rhs) noexcept { return !(lhs == rhs); }

inline bool operator==(const BinaryOutputMeasurements::Imu& lhs, const BinaryOutputMeasurements::Imu& rhs) noexcept
{
    return static_cast<uint32_t>(lhs) == static_cast<uint32_t>(rhs);
}
inline bool operator!=(const BinaryOutputMeasurements::Imu& lhs, const BinaryOutputMeasurements::Imu& rhs) noexcept { return !(lhs == rhs); }

inline bool operator==(const BinaryOutputMeasurements::Gnss& lhs, const BinaryOutputMeasurements::Gnss& rhs) noexcept
{
    return static_cast<uint32_t>(lhs) == static_cast<uint32_t>(rhs);
}
inline bool operator!=(const BinaryOutputMeasurements::Gnss& lhs, const BinaryOutputMeasurements::Gnss& rhs) noexcept { return !(lhs == rhs); }

inline bool operator==(const BinaryOutputMeasurements::Attitude& lhs, const BinaryOutputMeasurements::Attitude& rhs) noexcept
{
    return static_cast<uint32_t>(lhs) == static_cast<uint32_t>(rhs);
}
inline bool operator!=(const BinaryOutputMeasurements::Attitude& lhs, const BinaryOutputMeasurements::Attitude& rhs) noexcept { return !(lhs == rhs); }

inline bool operator==(const BinaryOutputMeasurements::Ins& lhs, const BinaryOutputMeasurements::Ins& rhs) noexcept
{
    return static_cast<uint32_t>(lhs) == static_cast<uint32_t>(rhs);
}
inline bool operator!=(const BinaryOutputMeasurements::Ins& lhs, const BinaryOutputMeasurements::Ins& rhs) noexcept { return !(lhs == rhs); }

inline bool operator==(const BinaryOutputMeasurements::Gnss2& lhs, const BinaryOutputMeasurements::Gnss2& rhs) noexcept
{
    return static_cast<uint32_t>(lhs) == static_cast<uint32_t>(rhs);
}
inline bool operator!=(const BinaryOutputMeasurements::Gnss2& lhs, const BinaryOutputMeasurements::Gnss2& rhs) noexcept { return !(lhs == rhs); }

inline bool operator==(const BinaryOutputMeasurements::Gnss3& lhs, const BinaryOutputMeasurements::Gnss3& rhs) noexcept
{
    return static_cast<uint32_t>(lhs) == static_cast<uint32_t>(rhs);
}
inline bool operator!=(const BinaryOutputMeasurements::Gnss3& lhs, const BinaryOutputMeasurements::Gnss3& rhs) noexcept { return !(lhs == rhs); }

class BinaryOutput : public ConfigurationRegister, public BinaryOutputMeasurements
{
public:
    using ConfigurationRegister::ConfigurationRegister;

    struct AsyncMode
    {
        uint16_t serial1 : 1;
        uint16_t serial2 : 1;
        uint16_t : 14;  // padding

        AsyncMode() noexcept : AsyncMode(0) {}
        AsyncMode(uint16_t in) noexcept { std::memcpy(this, &in, sizeof(AsyncMode)); }

        explicit operator uint16_t() const
        {
            uint16_t result;
            std::memcpy(&result, this, sizeof(AsyncMode));
            return result;
        }
        AsyncMode& operator=(const uint16_t& other)
        {
            std::memcpy(this, &other, sizeof(AsyncMode));
            return *this;
        }
    };
    static_assert(sizeof(AsyncMode) == 2);

    std::optional<AsyncMode> asyncMode;
    std::optional<uint16_t> rateDivisor;

    bool fromString(const AsciiMessage& sensorResponsePayload) override;
    AsciiMessage toString() const override;

protected:
    using Register::_id;
};

inline bool operator==(const BinaryOutput::AsyncMode& lhs, const BinaryOutput::AsyncMode& rhs) noexcept
{
    return static_cast<uint16_t>(lhs) == static_cast<uint16_t>(rhs);
}
inline bool operator!=(const BinaryOutput::AsyncMode& lhs, const BinaryOutput::AsyncMode& rhs) noexcept { return !(lhs == rhs); }

inline bool operator==(const BinaryOutput& lhs, const BinaryOutput& rhs) noexcept
{
    return ((lhs.asyncMode == rhs.asyncMode) && (lhs.rateDivisor == rhs.rateDivisor) && (lhs.common == rhs.common) && (lhs.time == rhs.time) &&
            (lhs.imu == rhs.imu) && (lhs.gnss == rhs.gnss) && (lhs.attitude == rhs.attitude) && (lhs.ins == rhs.ins) && (lhs.gnss2 == rhs.gnss2) &&
            (lhs.gnss3 == rhs.gnss3));
}

class BinaryOutput1 : public BinaryOutput
{
public:
    BinaryOutput1() : BinaryOutput{75} {}
    static constexpr const char* name() { return "BinaryOutput1"; };
};

class BinaryOutput2 : public BinaryOutput
{
public:
    BinaryOutput2() : BinaryOutput{76} {}
    static constexpr const char* name() { return "BinaryOutput2"; };
};

class BinaryOutput3 : public BinaryOutput
{
public:
    BinaryOutput3() : BinaryOutput{77} {}
    static constexpr const char* name() { return "BinaryOutput3"; };
};

/**--------------------------------------------------------------------------------------------------
<summary> Register 101 - NMEA Output 1 </summary>
<remarks>
</remarks>
*-----------------------------------------------------------------------------------------------**/
class NmeaOutput1 : public ConfigurationRegister
{
public:
    enum class Port : uint8_t
    {
        None = 0,
        Serial1 = 1,
        Serial2 = 2,
        Serial1And2 = 3,
    };

    enum class Rate : uint8_t
    {
        Rate0Hz = 0,
        Rate1Hz = 1,
        Rate5Hz = 5,
        Rate10Hz = 10,
        Rate20Hz = 20,
    };

    enum class Mode : uint8_t
    {
        V41GPID = 0,
        V23GPID = 1,
        V41SYSID = 2,
    };

    enum class GnssSelect : uint8_t
    {
        GnssA = 0,
        ActiveReceiver = 1,
    };

    struct MsgSelection
    {
        uint32_t rmcGnss : 1;
        uint32_t rmcIns : 1;
        uint32_t ggaGnss : 1;
        uint32_t ggaIns : 1;
        uint32_t gllGnss : 1;
        uint32_t gllIns : 1;
        uint32_t gsaGnss : 1;
        uint32_t gsvGnss : 1;
        uint32_t hdgIns : 1;
        uint32_t hdtIns : 1;
        uint32_t thsIns : 1;
        uint32_t vtgGnss : 1;
        uint32_t vtgIns : 1;
        uint32_t zdaGnss : 1;
        uint32_t zdaIns : 1;
        uint32_t pashrIns : 1;
        uint32_t tss1Ins : 1;
        uint32_t indyn : 1;
        uint32_t : 14;  // padding

        MsgSelection() noexcept : MsgSelection(0) {}
        MsgSelection(uint32_t in) noexcept { std::memcpy(this, &in, sizeof(MsgSelection)); }

        explicit operator uint32_t() const
        {
            uint32_t result;
            std::memcpy(&result, this, sizeof(MsgSelection));
            return result;
        }

        MsgSelection& operator=(const uint32_t& other)
        {
            std::memcpy(this, &other, sizeof(MsgSelection));
            return *this;
        }
    };
    static_assert(sizeof(MsgSelection) == 4);

    std::optional<Port> port;
    std::optional<Rate> rate;
    std::optional<Mode> mode;
    std::optional<GnssSelect> gnssSelect;
    std::optional<MsgSelection> msgSelection;

    NmeaOutput1() : ConfigurationRegister(101) {}
    static constexpr const char* name() { return "NmeaOutput1"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    AsciiMessage toString() const override;
};

inline bool operator==(const NmeaOutput1::MsgSelection& lhs, const NmeaOutput1::MsgSelection& rhs) noexcept
{
    return static_cast<uint32_t>(lhs) == static_cast<uint32_t>(rhs);
}
inline bool operator!=(const NmeaOutput1::MsgSelection& lhs, const NmeaOutput1::MsgSelection& rhs) noexcept { return !(lhs == rhs); }

inline bool operator==(const NmeaOutput1& lhs, const NmeaOutput1& rhs)
{
    return ((lhs.port == rhs.port) && (lhs.rate == rhs.rate) && (lhs.mode == rhs.mode) && (lhs.gnssSelect == rhs.gnssSelect) &&
            (lhs.msgSelection == rhs.msgSelection));
}

inline bool operator!=(const NmeaOutput1& lhs, const NmeaOutput1& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 102 - NMEA Output 2 </summary>
<remarks>
</remarks>
*-----------------------------------------------------------------------------------------------**/
class NmeaOutput2 : public ConfigurationRegister
{
public:
    enum class Port : uint8_t
    {
        None = 0,
        Serial1 = 1,
        Serial2 = 2,
        Serial1And2 = 3,
    };

    enum class Rate : uint8_t
    {
        Rate0Hz = 0,
        Rate1Hz = 1,
        Rate5Hz = 5,
        Rate10Hz = 10,
        Rate20Hz = 20,
    };

    enum class Mode : uint8_t
    {
        V41GPID = 0,
        V23GPID = 1,
        V41SYSID = 2,
    };

    enum class GnssSelect : uint8_t
    {
        GnssA = 0,
        ActiveReceiver = 1,
    };

    struct MsgSelection
    {
        uint32_t rmcGnss : 1;
        uint32_t rmcIns : 1;
        uint32_t ggaGnss : 1;
        uint32_t ggaIns : 1;
        uint32_t gllGnss : 1;
        uint32_t gllIns : 1;
        uint32_t gsaGnss : 1;
        uint32_t gsvGnss : 1;
        uint32_t hdgIns : 1;
        uint32_t hdtIns : 1;
        uint32_t thsIns : 1;
        uint32_t vtgGnss : 1;
        uint32_t vtgIns : 1;
        uint32_t zdaGnss : 1;
        uint32_t zdaIns : 1;
        uint32_t pashrIns : 1;
        uint32_t tss1Ins : 1;
        uint32_t indyn : 1;
        uint32_t : 14;  // padding

        MsgSelection() noexcept : MsgSelection(0) {}
        MsgSelection(uint32_t in) noexcept { std::memcpy(this, &in, sizeof(MsgSelection)); }

        explicit operator uint32_t() const
        {
            uint32_t result;
            std::memcpy(&result, this, sizeof(MsgSelection));
            return result;
        }

        MsgSelection& operator=(const uint32_t& other)
        {
            std::memcpy(this, &other, sizeof(MsgSelection));
            return *this;
        }
    };
    static_assert(sizeof(MsgSelection) == 4);

    std::optional<Port> port;
    std::optional<Rate> rate;
    std::optional<Mode> mode;
    std::optional<GnssSelect> gnssSelect;
    std::optional<MsgSelection> msgSelection;

    NmeaOutput2() : ConfigurationRegister(102) {}
    static constexpr const char* name() { return "NmeaOutput2"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    AsciiMessage toString() const override;
};

inline bool operator==(const NmeaOutput2::MsgSelection& lhs, const NmeaOutput2::MsgSelection& rhs) noexcept
{
    return static_cast<uint32_t>(lhs) == static_cast<uint32_t>(rhs);
}
inline bool operator!=(const NmeaOutput2::MsgSelection& lhs, const NmeaOutput2::MsgSelection& rhs) noexcept { return !(lhs == rhs); }

inline bool operator==(const NmeaOutput2& lhs, const NmeaOutput2& rhs)
{
    return ((lhs.port == rhs.port) && (lhs.rate == rhs.rate) && (lhs.mode == rhs.mode) && (lhs.gnssSelect == rhs.gnssSelect) &&
            (lhs.msgSelection == rhs.msgSelection));
}

inline bool operator!=(const NmeaOutput2& lhs, const NmeaOutput2& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 206 - Legacy Compatibility Settings </summary>
<remarks>
</remarks>
*-----------------------------------------------------------------------------------------------**/
class LegacyCompatibilitySettings : public ConfigurationRegister
{
public:
    enum class InsLegacy : uint8_t
    {
        Current = 0,
        Legacy = 1,
    };

    struct GnssLegacy
    {
        uint8_t legacyGnssFix : 1;
        uint8_t requireReg55Reset : 1;
        uint8_t alwaysPpsPulse : 1;
        uint8_t : 5;  // padding

        GnssLegacy() noexcept : GnssLegacy(0) {}
        GnssLegacy(uint8_t in) noexcept { std::memcpy(this, &in, sizeof(GnssLegacy)); }

        explicit operator uint8_t() const
        {
            uint8_t result;
            std::memcpy(&result, this, sizeof(GnssLegacy));
            return result;
        }

        GnssLegacy& operator=(const uint8_t& other)
        {
            std::memcpy(this, &other, sizeof(GnssLegacy));
            return *this;
        }
    };
    static_assert(sizeof(GnssLegacy) == 1);

    enum class ImuLegacy : uint8_t
    {
        Current = 0,
        Legacy = 1,
    };

    enum class HwLegacy : uint8_t
    {
        Current = 0,
        Legacy = 1,
    };

    std::optional<InsLegacy> insLegacy;
    std::optional<GnssLegacy> gnssLegacy;
    std::optional<ImuLegacy> imuLegacy;
    std::optional<HwLegacy> hwLegacy;

    LegacyCompatibilitySettings() : ConfigurationRegister(206) {}
    static constexpr const char* name() { return "LegacyCompatibilitySettings"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    AsciiMessage toString() const override;
};

inline bool operator==(const LegacyCompatibilitySettings::GnssLegacy& lhs, const LegacyCompatibilitySettings::GnssLegacy& rhs) noexcept
{
    return static_cast<uint8_t>(lhs) == static_cast<uint8_t>(rhs);
}
inline bool operator!=(const LegacyCompatibilitySettings::GnssLegacy& lhs, const LegacyCompatibilitySettings::GnssLegacy& rhs) noexcept
{
    return !(lhs == rhs);
}

inline bool operator==(const LegacyCompatibilitySettings& lhs, const LegacyCompatibilitySettings& rhs)
{
    return ((lhs.insLegacy == rhs.insLegacy) && (lhs.gnssLegacy == rhs.gnssLegacy) && (lhs.imuLegacy == rhs.imuLegacy) && (lhs.hwLegacy == rhs.hwLegacy));
}

inline bool operator!=(const LegacyCompatibilitySettings& lhs, const LegacyCompatibilitySettings& rhs) { return !(lhs == rhs); }
}  // namespace System

namespace VelocityAiding
{
/**--------------------------------------------------------------------------------------------------
<summary> Register 50 - Velocity Aiding Measurement </summary>
<remarks>
</remarks>
*-----------------------------------------------------------------------------------------------**/
class VelAidingMeas : public ConfigurationRegister
{
public:
    std::optional<float> velocityX;
    std::optional<float> velocityY;
    std::optional<float> velocityZ;

    VelAidingMeas() : ConfigurationRegister(50) {}
    static constexpr const char* name() { return "VelAidingMeas"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    AsciiMessage toString() const override;
};

inline bool operator==(const VelAidingMeas& lhs, const VelAidingMeas& rhs)
{
    return ((lhs.velocityX == rhs.velocityX) && (lhs.velocityY == rhs.velocityY) && (lhs.velocityZ == rhs.velocityZ));
}

inline bool operator!=(const VelAidingMeas& lhs, const VelAidingMeas& rhs) { return !(lhs == rhs); }
/**--------------------------------------------------------------------------------------------------
<summary> Register 51 - Velocity Aiding Control </summary>
<remarks>
</remarks>
*-----------------------------------------------------------------------------------------------**/
class VelAidingControl : public ConfigurationRegister
{
public:
    enum class VelAidEnable : uint8_t
    {
        Disable = 0,
        Enable = 1,
    };

    std::optional<VelAidEnable> velAidEnable;
    std::optional<float> velUncertTuning;
    std::optional<float> resv;

    VelAidingControl() : ConfigurationRegister(51) {}
    static constexpr const char* name() { return "VelAidingControl"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    AsciiMessage toString() const override;
};

inline bool operator==(const VelAidingControl& lhs, const VelAidingControl& rhs)
{
    return ((lhs.velAidEnable == rhs.velAidEnable) && (lhs.velUncertTuning == rhs.velUncertTuning) && (lhs.resv == rhs.resv));
}

inline bool operator!=(const VelAidingControl& lhs, const VelAidingControl& rhs) { return !(lhs == rhs); }
}  // namespace VelocityAiding

namespace WorldMagGravityModel
{
/**--------------------------------------------------------------------------------------------------
<summary> Register 83 - Reference Model Configuration </summary>
<remarks>
</remarks>
*-----------------------------------------------------------------------------------------------**/
class RefModelConfig : public ConfigurationRegister
{
public:
    enum class EnableMagModel : uint8_t
    {
        Disabled = 0,
        Enabled = 1,
    };

    enum class EnableGravityModel : uint8_t
    {
        Disabled = 0,
        Enabled = 1,
    };

    std::optional<EnableMagModel> enableMagModel;
    std::optional<EnableGravityModel> enableGravityModel;
    std::optional<uint8_t> resv1;
    std::optional<uint8_t> resv2;
    std::optional<uint32_t> recalcThreshold;
    std::optional<float> year;
    std::optional<double> latitude;
    std::optional<double> longitude;
    std::optional<double> altitude;

    RefModelConfig() : ConfigurationRegister(83) {}
    static constexpr const char* name() { return "RefModelConfig"; };

    bool fromString(const AsciiMessage& sensorResponse) override;
    AsciiMessage toString() const override;
};

inline bool operator==(const RefModelConfig& lhs, const RefModelConfig& rhs)
{
    return ((lhs.enableMagModel == rhs.enableMagModel) && (lhs.enableGravityModel == rhs.enableGravityModel) && (lhs.resv1 == rhs.resv1) &&
            (lhs.resv2 == rhs.resv2) && (lhs.recalcThreshold == rhs.recalcThreshold) && (lhs.year == rhs.year) && (lhs.latitude == rhs.latitude) &&
            (lhs.longitude == rhs.longitude) && (lhs.altitude == rhs.altitude));
}

inline bool operator!=(const RefModelConfig& lhs, const RefModelConfig& rhs) { return !(lhs == rhs); }
}  // namespace WorldMagGravityModel

namespace ById
{
using Reg0 = Registers::System::UserTag;
using Reg1 = Registers::System::Model;
using Reg2 = Registers::System::HwVer;
using Reg3 = Registers::System::Serial;
using Reg4 = Registers::System::FwVer;
using Reg5 = Registers::System::BaudRate;
using Reg6 = Registers::System::AsyncOutputType;
using Reg7 = Registers::System::AsyncOutputFreq;
using Reg8 = Registers::Attitude::YawPitchRoll;
using Reg9 = Registers::Attitude::Quaternion;
using Reg15 = Registers::Attitude::QuatMagAccelRate;
using Reg17 = Registers::IMU::Mag;
using Reg18 = Registers::IMU::Accel;
using Reg19 = Registers::IMU::Gyro;
using Reg20 = Registers::IMU::MagAccelGyro;
using Reg21 = Registers::Attitude::MagGravRefVec;
using Reg23 = Registers::IMU::MagCal;
using Reg25 = Registers::IMU::AccelCal;
using Reg26 = Registers::IMU::RefFrameRot;
using Reg27 = Registers::Attitude::YprMagAccelAngularRates;
using Reg30 = Registers::System::ProtocolControl;
using Reg32 = Registers::System::SyncControl;
using Reg33 = Registers::System::SyncStatus;
using Reg35 = Registers::Attitude::VpeBasicControl;
using Reg36 = Registers::Attitude::VpeMagBasicTuning;
using Reg38 = Registers::Attitude::VpeAccelBasicTuning;
using Reg44 = Registers::HardSoftIronEstimator::RealTimeHsiControl;
using Reg47 = Registers::HardSoftIronEstimator::EstMagCal;
using Reg50 = Registers::VelocityAiding::VelAidingMeas;
using Reg51 = Registers::VelocityAiding::VelAidingControl;
using Reg54 = Registers::IMU::ImuMeas;
using Reg55 = Registers::GNSS::GnssBasicConfig;
using Reg57 = Registers::GNSS::GnssAOffset;
using Reg58 = Registers::GNSS::GnssSolLla;
using Reg59 = Registers::GNSS::GnssSolEcef;
using Reg63 = Registers::INS::InsSolLla;
using Reg64 = Registers::INS::InsSolEcef;
using Reg67 = Registers::INS::InsBasicConfig;
using Reg72 = Registers::INS::InsStateLla;
using Reg73 = Registers::INS::InsStateEcef;
using Reg74 = Registers::INS::FilterStartupBias;
using Reg75 = Registers::System::BinaryOutput1;
using Reg76 = Registers::System::BinaryOutput2;
using Reg77 = Registers::System::BinaryOutput3;
using Reg80 = Registers::IMU::DeltaThetaVelocity;
using Reg82 = Registers::IMU::DeltaThetaVelConfig;
using Reg83 = Registers::WorldMagGravityModel::RefModelConfig;
using Reg84 = Registers::IMU::GyroCal;
using Reg85 = Registers::IMU::ImuFilterControl;
using Reg86 = Registers::GNSSCompass::GnssCompassSignalHealthStatus;
using Reg93 = Registers::GNSSCompass::GnssCompassBaseline;
using Reg97 = Registers::GNSSCompass::GnssCompassEstBaseline;
using Reg98 = Registers::GNSSCompass::GnssCompassStartupStatus;
using Reg99 = Registers::GNSS::GnssSystemConfig;
using Reg100 = Registers::GNSS::GnssSyncConfig;
using Reg101 = Registers::System::NmeaOutput1;
using Reg102 = Registers::System::NmeaOutput2;
using Reg103 = Registers::GNSS::Gnss2SolLla;
using Reg104 = Registers::GNSS::Gnss2SolEcef;
using Reg105 = Registers::INS::InsRefOffset;
using Reg115 = Registers::Heave::HeaveOutputs;
using Reg116 = Registers::Heave::HeaveBasicConfig;
using Reg144 = Registers::INS::InsGnssSelect;
using Reg157 = Registers::GNSS::ExtGnssOffset;
using Reg206 = Registers::System::LegacyCompatibilitySettings;
using Reg239 = Registers::Attitude::YprLinearBodyAccelAngularRates;
using Reg240 = Registers::Attitude::YprLinearInertialAccelAngularRates;
}  // namespace ById

inline bool isConfigEqual(const VN::ConfigurationRegister& lhs, const VN::ConfigurationRegister& rhs)
{
    using namespace VN::Registers::ById;

    if (lhs.id() != rhs.id()) { return false; }

    switch (lhs.id())
    {
        case 0:
            return static_cast<const Reg0&>(lhs) == static_cast<const Reg0&>(rhs);
        case 5:
            return static_cast<const Reg5&>(lhs) == static_cast<const Reg5&>(rhs);
        case 6:
            return static_cast<const Reg6&>(lhs) == static_cast<const Reg6&>(rhs);
        case 7:
            return static_cast<const Reg7&>(lhs) == static_cast<const Reg7&>(rhs);
        case 21:
            return static_cast<const Reg21&>(lhs) == static_cast<const Reg21&>(rhs);
        case 23:
            return static_cast<const Reg23&>(lhs) == static_cast<const Reg23&>(rhs);
        case 25:
            return static_cast<const Reg25&>(lhs) == static_cast<const Reg25&>(rhs);
        case 26:
            return static_cast<const Reg26&>(lhs) == static_cast<const Reg26&>(rhs);
        case 30:
            return static_cast<const Reg30&>(lhs) == static_cast<const Reg30&>(rhs);
        case 32:
            return static_cast<const Reg32&>(lhs) == static_cast<const Reg32&>(rhs);
        case 35:
            return static_cast<const Reg35&>(lhs) == static_cast<const Reg35&>(rhs);
        case 36:
            return static_cast<const Reg36&>(lhs) == static_cast<const Reg36&>(rhs);
        case 38:
            return static_cast<const Reg38&>(lhs) == static_cast<const Reg38&>(rhs);
        case 44:
            return static_cast<const Reg44&>(lhs) == static_cast<const Reg44&>(rhs);
        case 50:
            return static_cast<const Reg50&>(lhs) == static_cast<const Reg50&>(rhs);
        case 51:
            return static_cast<const Reg51&>(lhs) == static_cast<const Reg51&>(rhs);
        case 55:
            return static_cast<const Reg55&>(lhs) == static_cast<const Reg55&>(rhs);
        case 57:
            return static_cast<const Reg57&>(lhs) == static_cast<const Reg57&>(rhs);
        case 67:
            return static_cast<const Reg67&>(lhs) == static_cast<const Reg67&>(rhs);
        case 74:
            return static_cast<const Reg74&>(lhs) == static_cast<const Reg74&>(rhs);
        case 75:
            return static_cast<const VN::Registers::System::BinaryOutput&>(lhs) == static_cast<const VN::Registers::System::BinaryOutput&>(rhs);
        case 76:
            return static_cast<const VN::Registers::System::BinaryOutput&>(lhs) == static_cast<const VN::Registers::System::BinaryOutput&>(rhs);
        case 77:
            return static_cast<const VN::Registers::System::BinaryOutput&>(lhs) == static_cast<const VN::Registers::System::BinaryOutput&>(rhs);
        case 82:
            return static_cast<const Reg82&>(lhs) == static_cast<const Reg82&>(rhs);
        case 83:
            return static_cast<const Reg83&>(lhs) == static_cast<const Reg83&>(rhs);
        case 84:
            return static_cast<const Reg84&>(lhs) == static_cast<const Reg84&>(rhs);
        case 85:
            return static_cast<const Reg85&>(lhs) == static_cast<const Reg85&>(rhs);
        case 93:
            return static_cast<const Reg93&>(lhs) == static_cast<const Reg93&>(rhs);
        case 99:
            return static_cast<const Reg99&>(lhs) == static_cast<const Reg99&>(rhs);
        case 100:
            return static_cast<const Reg100&>(lhs) == static_cast<const Reg100&>(rhs);
        case 101:
            return static_cast<const Reg101&>(lhs) == static_cast<const Reg101&>(rhs);
        case 102:
            return static_cast<const Reg102&>(lhs) == static_cast<const Reg102&>(rhs);
        case 105:
            return static_cast<const Reg105&>(lhs) == static_cast<const Reg105&>(rhs);
        case 116:
            return static_cast<const Reg116&>(lhs) == static_cast<const Reg116&>(rhs);
        case 144:
            return static_cast<const Reg144&>(lhs) == static_cast<const Reg144&>(rhs);
        case 157:
            return static_cast<const Reg157&>(lhs) == static_cast<const Reg157&>(rhs);
        case 206:
            return static_cast<const Reg206&>(lhs) == static_cast<const Reg206&>(rhs);
        default:
            abort();
            break;
    }

    return false;
}  // bool operator==

constexpr static std::optional<const char*> getConfigRegisterName(uint8_t regId)
{
    switch (regId)
    {
        case 0:
        {
            return VN::Registers::ById::Reg0::name();
        }
        case 5:
        {
            return VN::Registers::ById::Reg5::name();
        }
        case 6:
        {
            return VN::Registers::ById::Reg6::name();
        }
        case 7:
        {
            return VN::Registers::ById::Reg7::name();
        }
        case 21:
        {
            return VN::Registers::ById::Reg21::name();
        }
        case 23:
        {
            return VN::Registers::ById::Reg23::name();
        }
        case 25:
        {
            return VN::Registers::ById::Reg25::name();
        }
        case 26:
        {
            return VN::Registers::ById::Reg26::name();
        }
        case 30:
        {
            return VN::Registers::ById::Reg30::name();
        }
        case 32:
        {
            return VN::Registers::ById::Reg32::name();
        }
        case 35:
        {
            return VN::Registers::ById::Reg35::name();
        }
        case 36:
        {
            return VN::Registers::ById::Reg36::name();
        }
        case 38:
        {
            return VN::Registers::ById::Reg38::name();
        }
        case 44:
        {
            return VN::Registers::ById::Reg44::name();
        }
        case 50:
        {
            return VN::Registers::ById::Reg50::name();
        }
        case 51:
        {
            return VN::Registers::ById::Reg51::name();
        }
        case 55:
        {
            return VN::Registers::ById::Reg55::name();
        }
        case 57:
        {
            return VN::Registers::ById::Reg57::name();
        }
        case 67:
        {
            return VN::Registers::ById::Reg67::name();
        }
        case 74:
        {
            return VN::Registers::ById::Reg74::name();
        }
        case 75:
        {
            return VN::Registers::ById::Reg75::name();
        }
        case 76:
        {
            return VN::Registers::ById::Reg76::name();
        }
        case 77:
        {
            return VN::Registers::ById::Reg77::name();
        }
        case 82:
        {
            return VN::Registers::ById::Reg82::name();
        }
        case 83:
        {
            return VN::Registers::ById::Reg83::name();
        }
        case 84:
        {
            return VN::Registers::ById::Reg84::name();
        }
        case 85:
        {
            return VN::Registers::ById::Reg85::name();
        }
        case 93:
        {
            return VN::Registers::ById::Reg93::name();
        }
        case 99:
        {
            return VN::Registers::ById::Reg99::name();
        }
        case 100:
        {
            return VN::Registers::ById::Reg100::name();
        }
        case 101:
        {
            return VN::Registers::ById::Reg101::name();
        }
        case 102:
        {
            return VN::Registers::ById::Reg102::name();
        }
        case 105:
        {
            return VN::Registers::ById::Reg105::name();
        }
        case 116:
        {
            return VN::Registers::ById::Reg116::name();
        }
        case 144:
        {
            return VN::Registers::ById::Reg144::name();
        }
        case 157:
        {
            return VN::Registers::ById::Reg157::name();
        }
        case 206:
        {
            return VN::Registers::ById::Reg206::name();
        }
        default:
        {
            return std::nullopt;
        }
    }
}

constexpr static std::optional<const char*> getMeasurementRegisterName(uint8_t regId)
{
    switch (regId)
    {
        case 1:
        {
            return VN::Registers::ById::Reg1::name();
        }
        case 2:
        {
            return VN::Registers::ById::Reg2::name();
        }
        case 3:
        {
            return VN::Registers::ById::Reg3::name();
        }
        case 4:
        {
            return VN::Registers::ById::Reg4::name();
        }
        case 8:
        {
            return VN::Registers::ById::Reg8::name();
        }
        case 9:
        {
            return VN::Registers::ById::Reg9::name();
        }
        case 15:
        {
            return VN::Registers::ById::Reg15::name();
        }
        case 17:
        {
            return VN::Registers::ById::Reg17::name();
        }
        case 18:
        {
            return VN::Registers::ById::Reg18::name();
        }
        case 19:
        {
            return VN::Registers::ById::Reg19::name();
        }
        case 20:
        {
            return VN::Registers::ById::Reg20::name();
        }
        case 27:
        {
            return VN::Registers::ById::Reg27::name();
        }
        case 33:
        {
            return VN::Registers::ById::Reg33::name();
        }
        case 47:
        {
            return VN::Registers::ById::Reg47::name();
        }
        case 54:
        {
            return VN::Registers::ById::Reg54::name();
        }
        case 58:
        {
            return VN::Registers::ById::Reg58::name();
        }
        case 59:
        {
            return VN::Registers::ById::Reg59::name();
        }
        case 63:
        {
            return VN::Registers::ById::Reg63::name();
        }
        case 64:
        {
            return VN::Registers::ById::Reg64::name();
        }
        case 72:
        {
            return VN::Registers::ById::Reg72::name();
        }
        case 73:
        {
            return VN::Registers::ById::Reg73::name();
        }
        case 80:
        {
            return VN::Registers::ById::Reg80::name();
        }
        case 86:
        {
            return VN::Registers::ById::Reg86::name();
        }
        case 97:
        {
            return VN::Registers::ById::Reg97::name();
        }
        case 98:
        {
            return VN::Registers::ById::Reg98::name();
        }
        case 103:
        {
            return VN::Registers::ById::Reg103::name();
        }
        case 104:
        {
            return VN::Registers::ById::Reg104::name();
        }
        case 115:
        {
            return VN::Registers::ById::Reg115::name();
        }
        case 239:
        {
            return VN::Registers::ById::Reg239::name();
        }
        case 240:
        {
            return VN::Registers::ById::Reg240::name();
        }
        default:
        {
            return std::nullopt;
        }
    }
}

}  // namespace Registers
}  // namespace VN

#endif  // VN_REGISTERS_HPP_
