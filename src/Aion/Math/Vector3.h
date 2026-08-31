#pragma once

#include <algorithm>
#include <cmath>
#include <glm/geometric.hpp>
#include <glm/vec3.hpp>

namespace Aion
{

    struct Vector3
    {
        float x{0.0f};
        float y{0.0f};
        float z{0.0f};

        constexpr Vector3() = default;
        constexpr Vector3(float scalar) : x(scalar), y(scalar), z(scalar) {}
        constexpr Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

        Vector3(const glm::vec3& glmVec) : x(glmVec.x), y(glmVec.y), z(glmVec.z) {}

        Vector3 operator+(const Vector3& rhs) const { return {x + rhs.x, y + rhs.y, z + rhs.z}; }
        Vector3 operator-(const Vector3& rhs) const { return {x - rhs.x, y - rhs.y, z - rhs.z}; }
        Vector3 operator*(float scalar) const { return {x * scalar, y * scalar, z * scalar}; }
        Vector3 operator/(float scalar) const { return {x / scalar, y / scalar, z / scalar}; }

        Vector3& operator+=(const Vector3& rhs)
        {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            return *this;
        }
        Vector3& operator-=(const Vector3& rhs)
        {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            return *this;
        }
        Vector3& operator*=(float scalar)
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }

        bool operator==(const Vector3& rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z; }
        bool operator!=(const Vector3& rhs) const { return !(*this == rhs); }

        operator glm::vec3() const { return glm::vec3(x, y, z); }

        float Length() const { return std::sqrt(x * x + y * y + z * z); }

        Vector3 Normalized() const
        {
            float len = Length();
            return len > 0.0f ? *this / len : Vector3(0.0f);
        }
    };

    inline Vector3 Normalize(const Vector3& v)
    {
        return v.Normalized();
    }

    inline Vector3 Cross(const Vector3& a, const Vector3& b)
    {
        return Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
    }

    inline float Dot(const Vector3& a, const Vector3& b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    inline float Lerp(float a, float b, float t)
    {
        return a + (b - a) * t;
    }

    inline Vector3 Lerp(const Vector3& a, const Vector3& b, float t)
    {
        return {a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t};
    }

    using Vec3 = Vector3;
} // namespace Aion