#include "PerspectiveCamera.h"

namespace Aion
{
    PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float nearPlane, float farPlane)
        : m_fov(fov), m_aspect(aspect), m_near(nearPlane), m_far(farPlane)
    {
    }

    void PerspectiveCamera::SetAspect(float aspect)
    {
        m_aspect = aspect;
    }

    void PerspectiveCamera::SetFOV(float fov)
    {
        m_fov = fov;
    }

    Matrix4 PerspectiveCamera::GetProjectionMatrix() const
    {
        return Matrix4::Perspective(Math::Radians(m_fov), m_aspect, m_near, m_far);
    }
} // namespace Aion