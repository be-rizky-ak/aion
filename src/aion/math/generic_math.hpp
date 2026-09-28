#pragma once

#include <algorithm>
#include <cmath>
#include <type_traits>

#include "Aion/Math/Math.h"
#include "Aion/Math/Matrix4.h"
#include "Aion/Math/Quaternion.h"
#include "Aion/Math/Vector2.h"
#include "Aion/Math/Vector3.h"
#include "Aion/Math/Vector4.h"

namespace Aion
{
    namespace Math
    {
        // =========================================================================
        // Generic Template Trait Library - Math Utilities
        // =========================================================================

        // Clamp is provided for template types in Math.h:
        // template <typename T> inline T Clamp(T value, T min, T max)

        // Vector3 Clamp specialization
        inline Vector3 Clamp(const Vector3& v, const Vector3& minV, const Vector3& maxV)
        {
            return Vector3(
                ::Aion::Math::Clamp(v.x, minV.x, maxV.x),
                ::Aion::Math::Clamp(v.y, minV.y, maxV.y),
                ::Aion::Math::Clamp(v.z, minV.z, maxV.z)
            );
        }

        // Generic Lerp for scalar types
        template <typename T, typename U = float>
        constexpr T Lerp(const T& a, const T& b, U t)
        {
            return static_cast<T>(a + (b - a) * t);
        }

        // Vector2 Lerp overload
        inline Vector2 Lerp(const Vector2& a, const Vector2& b, float t)
        {
            return Vector2(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t);
        }

        // Vector3 Lerp overload
        inline Vector3 Lerp(const Vector3& a, const Vector3& b, float t)
        {
            return Vector3(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t);
        }

        // Vector4 Lerp overload
        inline Vector4 Lerp(const Vector4& a, const Vector4& b, float t)
        {
            return Vector4(
                a.x + (b.x - a.x) * t,
                a.y + (b.y - a.y) * t,
                a.z + (b.z - a.z) * t,
                a.w + (b.w - a.w) * t
            );
        }

        // Matrix Transformations
        template <typename MatrixType = Matrix4, typename VectorType = Vector3>
        inline MatrixType Translate(const VectorType& translation)
        {
            return MatrixType::Translate(translation);
        }

        template <typename MatrixType = Matrix4, typename VectorType = Vector3>
        inline MatrixType Rotate(float angleRadians, const VectorType& axis)
        {
            return MatrixType::Rotate(angleRadians, axis);
        }

        template <typename MatrixType = Matrix4>
        inline MatrixType Rotate(const Quaternion& rotation)
        {
            return MatrixType::Rotate(rotation);
        }

        template <typename MatrixType = Matrix4, typename VectorType = Vector3>
        inline MatrixType Scale(const VectorType& scale)
        {
            return MatrixType::Scale(scale);
        }

        template <typename MatrixType = Matrix4>
        inline MatrixType Perspective(float fovRadians, float aspectRatio, float zNear, float zFar)
        {
            return MatrixType::Perspective(fovRadians, aspectRatio, zNear, zFar);
        }

        template <typename MatrixType = Matrix4>
        inline MatrixType Ortho(float left, float right, float bottom, float top, float zNear, float zFar)
        {
            return MatrixType::Ortho(left, right, bottom, top, zNear, zFar);
        }

        template <typename MatrixType = Matrix4>
        inline MatrixType Inverse(const MatrixType& matrix)
        {
            return MatrixType::Inverse(matrix);
        }

        template <typename MatrixType = Matrix4>
        inline MatrixType Transpose(const MatrixType& matrix)
        {
            return MatrixType::Transpose(matrix);
        }

        // Generic MathTraits struct for traits-style access
        template <typename T>
        struct MathTraits
        {
            static constexpr T ClampValue(T val, T minV, T maxV)
            {
                return Clamp(val, minV, maxV);
            }

            template <typename U = float>
            static constexpr T LerpValue(const T& a, const T& b, U t)
            {
                return Lerp(a, b, t);
            }
        };

    } // namespace Math
} // namespace Aion

namespace aion
{
    namespace math = ::Aion::Math;
}
