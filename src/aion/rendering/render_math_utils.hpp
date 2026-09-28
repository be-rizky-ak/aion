#pragma once

#include "aion/math/generic_math.hpp"

namespace Aion
{
    namespace Rendering
    {
        // =========================================================================
        // Legacy Rendering Math Utilities (Deprecated Wrappers)
        // =========================================================================

        template <typename T>
        [[deprecated("RenderClamp is deprecated. Use Aion::Math::Clamp instead.")]]
        inline T RenderClamp(T val, T minVal, T maxVal)
        {
            return Aion::Math::Clamp(val, minVal, maxVal);
        }

        template <typename T, typename U = float>
        [[deprecated("RenderLerp is deprecated. Use Aion::Math::Lerp instead.")]]
        inline T RenderLerp(const T& a, const T& b, U t)
        {
            return Aion::Math::Lerp(a, b, t);
        }

        [[deprecated("RenderTranslate is deprecated. Use Aion::Math::Translate instead.")]]
        inline Matrix4 RenderTranslate(const Vector3& translation)
        {
            return Aion::Math::Translate(translation);
        }

        [[deprecated("RenderRotate is deprecated. Use Aion::Math::Rotate instead.")]]
        inline Matrix4 RenderRotate(float angleRadians, const Vector3& axis)
        {
            return Aion::Math::Rotate(angleRadians, axis);
        }

        [[deprecated("RenderRotate is deprecated. Use Aion::Math::Rotate instead.")]]
        inline Matrix4 RenderRotate(const Quaternion& rotation)
        {
            return Aion::Math::Rotate(rotation);
        }

        [[deprecated("RenderScale is deprecated. Use Aion::Math::Scale instead.")]]
        inline Matrix4 RenderScale(const Vector3& scale)
        {
            return Aion::Math::Scale(scale);
        }

        [[deprecated("RenderPerspective is deprecated. Use Aion::Math::Perspective instead.")]]
        inline Matrix4 RenderPerspective(float fovRadians, float aspectRatio, float zNear, float zFar)
        {
            return Aion::Math::Perspective(fovRadians, aspectRatio, zNear, zFar);
        }

        [[deprecated("RenderOrtho is deprecated. Use Aion::Math::Ortho instead.")]]
        inline Matrix4 RenderOrtho(float left, float right, float bottom, float top, float zNear, float zFar)
        {
            return Aion::Math::Ortho(left, right, bottom, top, zNear, zFar);
        }

        [[deprecated("RenderInverse is deprecated. Use Aion::Math::Inverse instead.")]]
        inline Matrix4 RenderInverse(const Matrix4& matrix)
        {
            return Aion::Math::Inverse(matrix);
        }

        [[deprecated("RenderTranspose is deprecated. Use Aion::Math::Transpose instead.")]]
        inline Matrix4 RenderTranspose(const Matrix4& matrix)
        {
            return Aion::Math::Transpose(matrix);
        }

    } // namespace Rendering
} // namespace Aion

namespace aion
{
    namespace rendering = ::Aion::Rendering;
}
