#pragma once

#include "Camera.h"

namespace Aion
{
    class OrthographicCamera : public Camera
    {
    public:
        OrthographicCamera(
            float left, float right, float bottom, float top, float nearPlane, float farPlane);

        Matrix4 GetProjectionMatrix() const override;

    private:
        float m_left;
        float m_right;
        float m_bottom;
        float m_top;
        float m_near;
        float m_far;
    };
} // namespace Aion