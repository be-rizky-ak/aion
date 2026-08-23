#pragma once

#include <cmath>
#include <glm/vec2.hpp>

namespace Aion
{

    struct Vector2
    {
        float x{0.0f};
        float y{0.0f};

        constexpr Vector2() = default;
        constexpr Vector2(float scalar) : x(scalar), y(scalar) {}
        constexpr Vector2(float x, float y) : x(x), y(y) {}

        Vector2(const glm::vec2& glmVec) : x(glmVec.x), y(glmVec.y) {}
        operator glm::vec2() const { return glm::vec2(x, y); }

        Vector2 operator+(const Vector2& rhs) const { return {x + rhs.x, y + rhs.y}; }
        Vector2 operator-(const Vector2& rhs) const { return {x - rhs.x, y - rhs.y}; }
        Vector2 operator*(float scalar) const { return {x * scalar, y * scalar}; }
        Vector2 operator/(float scalar) const { return {x / scalar, y / scalar}; }

        Vector2& operator+=(const Vector2& rhs)
        {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }
        Vector2& operator-=(const Vector2& rhs)
        {
            x -= rhs.x;
            y -= rhs.y;
            return *this;
        }
        Vector2& operator*=(float scalar)
        {
            x *= scalar;
            y *= scalar;
            return *this;
        }

        bool operator==(const Vector2& rhs) const { return x == rhs.x && y == rhs.y; }
        bool operator!=(const Vector2& rhs) const { return !(*this == rhs); }

        float Length() const { return std::sqrt(x * x + y * y); }

        Vector2 Normalized() const
        {
            float len = Length();
            return len > 0.0f ? *this / len : Vector2(0.0f);
        }
    };

    using Vec2 = Vector2;

} // namespace Aion