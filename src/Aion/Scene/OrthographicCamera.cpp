#include "OrthographicCamera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Aion
{
    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top,
                                           float nearPlane, float farPlane)
        : m_left(left), m_right(right), m_bottom(bottom), m_top(top), m_near(nearPlane),
          m_far(farPlane)
    {
    }

    Matrix4 OrthographicCamera::GetProjectionMatrix() const
    {
        return Matrix4::Ortho(m_left, m_right, m_bottom, m_top, m_near, m_far);
    }
} // namespace Aion