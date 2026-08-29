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

        Quaternion operator*(const Quaternion& rhs) const
        {
            return Quaternion(w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y,
                w * rhs.y - x * rhs.z + y * rhs.w + z * rhs.x,
                w * rhs.z + x * rhs.y - y * rhs.x + z * rhs.w,
                w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z);
        }
    };
} // namespace Aion