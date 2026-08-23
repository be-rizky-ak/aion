#pragma once

#include "Aion/Math/Vector3.h"
#include "Aion/Math/Vector4.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>

namespace Aion
{

    struct Matrix4
    {
        Vector4 Columns[4]{Vector4(1.0f, 0.0f, 0.0f, 0.0f), Vector4(0.0f, 1.0f, 0.0f, 0.0f),
            Vector4(0.0f, 0.0f, 1.0f, 0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f)};

        Matrix4() = default;

        explicit Matrix4(float diagonal)
        {
            Columns[0] = Vector4(diagonal, 0.0f, 0.0f, 0.0f);
            Columns[1] = Vector4(0.0f, diagonal, 0.0f, 0.0f);
            Columns[2] = Vector4(0.0f, 0.0f, diagonal, 0.0f);
            Columns[3] = Vector4(0.0f, 0.0f, 0.0f, diagonal);
        }

        Matrix4(const glm::mat4& glmMat)
        {
            Columns[0] = Vector4(glmMat[0]);
            Columns[1] = Vector4(glmMat[1]);
            Columns[2] = Vector4(glmMat[2]);
            Columns[3] = Vector4(glmMat[3]);
        }

        operator glm::mat4() const
        {
            return glm::mat4((glm::vec4)Columns[0], (glm::vec4)Columns[1], (glm::vec4)Columns[2],
                (glm::vec4)Columns[3]);
        }

        const float* ValuePtr() const { return &Columns[0].x; }

        Matrix4 operator*(const Matrix4& rhs) const
        {
            return Matrix4((glm::mat4) * this * (glm::mat4)rhs);
        }

        Vector4 operator*(const Vector4& rhs) const
        {
            glm::vec4 result = (glm::mat4) * this * (glm::vec4)rhs;
            return Vector4(result);
        }

        static Matrix4 Identity() { return Matrix4(1.0f); }

        static Matrix4 Translate(const Vector3& translation)
        {
            return Matrix4(glm::translate(glm::mat4(1.0f), static_cast<glm::vec3>(translation)));
        }

        static Matrix4 Rotate(float angleRadians, const Vector3& axis)
        {
            return Matrix4(
                glm::rotate(glm::mat4(1.0f), angleRadians, static_cast<glm::vec3>(axis)));
        }

        static Matrix4 Scale(const Vector3& scale)
        {
            return Matrix4(glm::scale(glm::mat4(1.0f), static_cast<glm::vec3>(scale)));
        }

        static Matrix4 Perspective(float fovRadians, float aspectRatio, float zNear, float zFar)
        {
            return Matrix4(glm::perspective(fovRadians, aspectRatio, zNear, zFar));
        }

        static Matrix4 Ortho(
            float left, float right, float bottom, float top, float zNear, float zFar)
        {
            return Matrix4(glm::ortho(left, right, bottom, top, zNear, zFar));
        }

        static Matrix4 Inverse(const Matrix4& matrix)
        {
            return Matrix4(glm::inverse((glm::mat4)matrix));
        }
    };

    using Mat4 = Matrix4;

} // namespace Aion