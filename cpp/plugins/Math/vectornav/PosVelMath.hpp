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

#ifndef VN_POSVELMATH_HPP_
#define VN_POSVELMATH_HPP_
#include <cmath>

#include "vectornav/Conversions.hpp"
#include "vectornav/Implementation/MeasurementDatatypes.hpp"
#include "vectornav/TemplateLibrary/Matrix.hpp"

namespace VN
{
namespace Math
{
inline float course_over_ground(float velNedX, float velNedY) noexcept { return std::atan2(velNedY, velNedX); }

inline float course_over_ground(const Vec3f& velNed) noexcept { return course_over_ground(velNed[0], velNed[1]); }

inline float speed_over_ground(const float velNedX, const float velNedY) noexcept { return std::sqrt(velNedX * velNedX + velNedY * velNedY); }

inline float speed_over_ground(const Vec3f& velNed) noexcept { return speed_over_ground(velNed[0], velNed[1]); }

constexpr double C_EARTHF = 0.003352810664747;
constexpr double C_EARTHR = 6378137.0;
constexpr double C_E2 = 0.0066943799901413295;
constexpr double C_EPSILON = 0.99664718933525254;
constexpr double C_ABAR = 42697.672707180049;
constexpr double C_BBAR = 42841.31151331366;

inline Lla ecef2lla(const Vec3d& ecef) noexcept
{
    double rho = std::sqrt(ecef[0] * ecef[0] + ecef[1] * ecef[1]);
    double beta = std::atan2(ecef[2], C_EPSILON * rho);
    double sb = std::sin(beta);
    double cb = std::cos(beta);
    double phi = std::atan2(ecef[2] + C_BBAR * sb * sb * sb, rho - C_ABAR * cb * cb * cb);
    double betaNew = std::atan2(C_EPSILON * std::sin(phi), std::cos(phi));

    int count = 0;
    while ((std::fabs(beta - betaNew) < 1e-11) && (count < 5))
    {
        beta = betaNew;
        sb = std::sin(betaNew);
        cb = std::cos(betaNew);
        phi = std::atan2(ecef[2] + C_BBAR * sb * sb * sb, rho - C_EPSILON * cb * cb * cb);
        betaNew = std::atan2(C_EPSILON * sin(phi), cos(phi));
        count++;
    }

    beta = std::sin(phi);
    betaNew = C_EARTHR / std::sqrt(1.0 - C_E2 * (beta * beta));

    return Lla{rad2deg(phi), rad2deg(std::atan2(ecef[1], ecef[0])), rho * std::cos(phi) + (ecef[2] + C_E2 * betaNew * beta) * beta - betaNew};
}

inline Vec3d lla2ecef(const Lla& lla) noexcept
{
    Lla llar{deg2rad(lla.lat), deg2rad(lla.lon), lla.alt};

    double comp_f_sq = (1 - C_EARTHF) * (1 - C_EARTHF);
    double lambda_s = std::atan(comp_f_sq * std::tan(llar.lat));

    double sinLam = std::sin(lambda_s);
    double cosLam = std::cos(lambda_s);
    double r_s = sqrt(C_EARTHR * C_EARTHR / (1.0 + (((1.0 / comp_f_sq) - 1.0) * sinLam * sinLam)));

    double cosLat = std::cos(llar.lat);
    double sinLat = std::sin(llar.lat);
    double cosLon = std::cos(llar.lon);
    double sinLon = std::sin(llar.lon);

    return Vec3d{
        (r_s * cosLam * cosLon) + (llar.alt * cosLat * cosLon),
        (r_s * cosLam * sinLon) + (llar.alt * cosLat * sinLon),
        (r_s * sinLam) + (llar.alt * sinLat),
    };
}

}  // namespace Math
}  // namespace VN

#endif  // VN_POSVELMATH_HPP_
