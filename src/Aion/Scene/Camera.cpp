#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float fov, float aspect, float nearClip, float farClip)
    : m_fov(fov)
    , m_aspect(aspect)
    , m_near(nearClip)
    , m_far(farClip)
    , m_yaw(-90.0f)
    , m_pitch(0.0f)
    , m_moveSpeed(3.0f)
    , m_mouseSensitivity(0.1f)
{
    UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() const
{
    return glm::lookAt(
        Transform.Position,
        Transform.Position + m_front,
        m_up
    );
}

glm::mat4 Camera::GetProjectionMatrix() const
{
    return glm::perspective(glm::radians(m_fov), m_aspect, m_near, m_far);
}

void Camera::ProcessKeyboard(
    float deltaTime,
    bool forward,
    bool backward,
    bool left,
    bool right)
{
    float velocity = m_moveSpeed * deltaTime;

    if (forward)
        Transform.Position += m_front * velocity;

    if (backward)
        Transform.Position -= m_front * velocity;

    if (left)
        Transform.Position -= m_right * velocity;

    if (right)
        Transform.Position += m_right * velocity;
}

void Camera::ProcessMouse(float xOffset, float yOffset)
{
    xOffset *= m_mouseSensitivity;
    yOffset *= m_mouseSensitivity;

    m_yaw += xOffset;
    m_pitch += yOffset;

    // Prevent camera flip
    if (m_pitch > 89.0f)
        m_pitch = 89.0f;

    if (m_pitch < -89.0f)
        m_pitch = -89.0f;

    UpdateCameraVectors();
}

void Camera::UpdateCameraVectors()
{
    glm::vec3 front;

    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

    m_front = glm::normalize(front);

    m_right = glm::normalize(
        glm::cross(
            m_front,
            glm::vec3(0.0f, 1.0f, 0.0f)
        )
    );

    m_up = glm::normalize(
        glm::cross(
            m_right,
            m_front
        )
    );
}