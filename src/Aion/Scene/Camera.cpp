#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Object3D.h"

Camera::Camera(float fov, float aspect, float nearClip, float farClip)
    : m_fov(fov), m_aspect(aspect), m_near(nearClip), m_far(farClip)
{
}

void Camera::SetAspect(float aspect)
{
    m_aspect = aspect;
}

float Camera::GetAspect() const
{
    return m_aspect;
}

glm::mat4 Camera::GetViewMatrix() const
{
    Object3D* owner = GetOwner();

    glm::vec3 position = owner->Transform.Position;

    float yaw = owner->Transform.Rotation.y;
    float pitch = owner->Transform.Rotation.x;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    return glm::lookAt(position, position + glm::normalize(front), glm::vec3(0, 1, 0));
}

glm::mat4 Camera::GetProjectionMatrix() const
{
    return glm::perspective(glm::radians(m_fov), m_aspect, m_near, m_far);
}