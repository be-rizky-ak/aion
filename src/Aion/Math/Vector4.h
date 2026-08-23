#pragma once

#include <cmath>
#include <glm/vec4.hpp>

namespace Aion
{

    struct Vector4
    {
        float x{0.0f};
        float y{0.0f};
        float z{0.0f};
        float w{0.0f};

        constexpr Vector4() = default;
        constexpr Vector4(float scalar) : x(scalar), y(scalar), z(scalar), w(scalar) {}
        constexpr Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

        // GLM Interoperability
        Vector4(const glm::vec4& glmVec) : x(glmVec.x), y(glmVec.y), z(glmVec.z), w(glmVec.w) {}
        operator glm::vec4() const { return glm::vec4(x, y, z, w); }

        // Operators
        Vector4 operator+(const Vector4& rhs) const
        {
            return {x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w};
        }
        Vector4 operator-(const Vector4& rhs) const
        {
            return {x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w};
        }
        Vector4 operator*(float scalar) const
        {
            return {x * scalar, y * scalar, z * scalar, w * scalar};
        }
        Vector4 operator/(float scalar) const
        {
            return {x / scalar, y / scalar, z / scalar, w / scalar};
        }

        Vector4& operator+=(const Vector4& rhs)
        {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            w += rhs.w;
            return *this;
        }
        Vector4& operator-=(const Vector4& rhs)
        {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            w -= rhs.w;
            return *this;
        }
        Vector4& operator*=(float scalar)
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            w *= scalar;
            return *this;
        }

        bool operator==(const Vector4& rhs) const
        {
            return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
        }
        bool operator!=(const Vector4& rhs) const { return !(*this == rhs); }

        float Length() const { return std::sqrt(x * x + y * y + z * z + w * w); }

        Vector4 Normalized() const
        {
            float len = Length();
            return len > 0.0f ? *this / len : Vector4(0.0f);
        }
    };

    using Vec4 = Vector4;

} // namespace Aion