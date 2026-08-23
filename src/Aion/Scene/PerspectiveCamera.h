#pragma once

#include "Camera.h"

#include "Aion/Math/Math.h"
#include "Aion/Math/Matrix4.h"

namespace Aion
{
    class PerspectiveCamera : public Camera
    {
    public:
        PerspectiveCamera(float fov, float aspect, float nearPlane, float farPlane);

        void SetAspect(float aspect) override;
        void SetFOV(float fov);

        Matrix4 GetProjectionMatrix() const override;

    private:
        float m_fov;
        float m_aspect;
        float m_near;
        float m_far;
    };
} // namespace Aion