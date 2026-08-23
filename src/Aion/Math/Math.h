#pragma once

#include <algorithm>
#include <cmath>

namespace Aion
{
    namespace Math
    {
        constexpr float Pi()
        {
            return 3.14159265358979323846f;
        }
        constexpr float HalfPi()
        {
            return 1.57079632679489661923f;
        }
        constexpr float TwoPi()
        {
            return 6.28318530717958647692f;
        }

        inline float Sin(float rad)
        {
            return std::sin(rad);
        }
        inline float Cos(float rad)
        {
            return std::cos(rad);
        }

        inline float Radians(float degrees)
        {
            return degrees * (Pi() / 180.0f);
        }

        inline float Degrees(float radians)
        {
            return radians * (180.0f / Pi());
        }

        template <typename T> inline T Clamp(T value, T min, T max)
        {
            return std::clamp(value, min, max);
        }
    } // namespace Math
} // namespace Aion