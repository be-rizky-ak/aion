#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float fov, float aspect, float nearClip, float farClip)
    : m_FOV(fov), m_Aspect(aspect), m_Near(nearClip), m_Far(farClip),
      m_Position(0.0f, 0.0f, 3.0f) // camera pulled back
{
}

glm::mat4 Camera::GetViewMatrix() const
{
    return glm::lookAt(
        m_Position,
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );
}

glm::mat4 Camera::GetProjectionMatrix() const
{
    return glm::perspective(glm::radians(m_FOV), m_Aspect, m_Near, m_Far);
}