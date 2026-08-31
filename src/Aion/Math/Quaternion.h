#pragma once

#include <cmath>

#include "Vector3.h"

namespace Aion
{
    struct Quaternion
    {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
        float w = 1.0f;

        Quaternion() = default;
        Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

        static Quaternion Identity() { return Quaternion(0.0f, 0.0f, 0.0f, 1.0f); }

        static Quaternion FromEuler(float pitch, float yaw, float roll)
        {
            float cy = std::cos(yaw * 0.5f);
            float sy = std::sin(yaw * 0.5f);
            float cp = std::cos(pitch * 0.5f);
            float sp = std::sin(pitch * 0.5f);
            float cr = std::cos(roll * 0.5f);
            float sr = std::sin(roll * 0.5f);

            Quaternion q;
            q.w = cr * cp * cy + sr * sp * sy;
            q.x = sr * cp * cy - cr * sp * sy;
            q.y = cr * sp * cy + sr * cp * sy;
            q.z = cr * cp * sy - sr * sp * cy;
            return q;
        }

        static Quaternion FromEuler(const Vector3& euler)
        {
            return FromEuler(euler.x, euler.y, euler.z);
        }

        static float Dot(const Quaternion& a, const Quaternion& b)
        {
            return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
        }

        Quaternion operator+(const Quaternion& rhs) const
        {
            return Quaternion(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
        }

        Quaternion operator-(const Quaternion& rhs) const
        {
            return Quaternion(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
        }

        Quaternion operator*(const Quaternion& rhs) const
        {
            return Quaternion(w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y,
                w * rhs.y - x * rhs.z + y * rhs.w + z * rhs.x,
                w * rhs.z + x * rhs.y - y * rhs.x + z * rhs.w,
                w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z);
        }

        Quaternion operator*(float scalar) const
        {
            return Quaternion(x * scalar, y * scalar, z * scalar, w * scalar);
        }

        Quaternion Normalized() const
        {
            float lenSq = x * x + y * y + z * z + w * w;

            if (lenSq <= 0.0f)
                return Identity();

            float invLen = 1.0f / std::sqrt(lenSq);

            return Quaternion(x * invLen, y * invLen, z * invLen, w * invLen);
        }

        static Quaternion Slerp(const Quaternion& a, const Quaternion& b, float t)
        {
            Quaternion end = b;

            float dot = Dot(a, b);

            // Take shortest path
            if (dot < 0.0f)
            {
                dot = -dot;
                end = b * -1.0f;
            }

            constexpr float DOT_THRESHOLD = 0.9995f;

            if (dot > DOT_THRESHOLD)
            {
                Quaternion result = a + (end - a) * t;

                return result.Normalized();
            }

            dot = std::clamp(dot, -1.0f, 1.0f);

            float theta0 = std::acos(dot);
            float theta = theta0 * t;

            float sinTheta = std::sin(theta);
            float sinTheta0 = std::sin(theta0);

            float s0 = std::cos(theta) - dot * sinTheta / sinTheta0;

            float s1 = sinTheta / sinTheta0;

            return Quaternion(a.x * s0 + end.x * s1, a.y * s0 + end.y * s1, a.z * s0 + end.z * s1,
                a.w * s0 + end.w * s1);
        }
    };
} // namespace Aion