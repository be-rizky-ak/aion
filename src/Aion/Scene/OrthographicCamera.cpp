#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

OrthographicCamera::OrthographicCamera(
    float left,
    float right,
    float bottom,
    float top,
    float nearPlane,
    float farPlane)
    :
    Camera(
        45.0f,
        1.0f,
        nearPlane,
        farPlane
    ),
    m_left(left),
    m_right(right),
    m_bottom(bottom),
    m_top(top)
{
}

glm::mat4 OrthographicCamera::GetProjectionMatrix() const
{
    return glm::ortho(
        m_left,
        m_right,
        m_bottom,
        m_top,
        m_near,
        m_far
    );
}