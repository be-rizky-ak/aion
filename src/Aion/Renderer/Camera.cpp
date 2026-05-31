#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float fov, float aspect, float nearClip, float farClip)
    : m_FOV(fov)
    , m_Aspect(aspect)
    , m_Near(nearClip)
    , m_Far(farClip)
    , m_Position(0.0f, 0.0f, 3.0f) // camera pulled back
    , m_Yaw(-90.0f)
    , m_Pitch(0.0f)
    , m_MoveSpeed(3.0f)
    , m_MouseSensitivity(0.1f)
{
    UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() const
{
    return glm::lookAt(
        m_Position,
        m_Position + m_Front,
        m_Up
    );
}

glm::mat4 Camera::GetProjectionMatrix() const
{
    return glm::perspective(glm::radians(m_FOV), m_Aspect, m_Near, m_Far);
}

void Camera::ProcessKeyboard(
    float deltaTime,
    bool forward,
    bool backward,
    bool left,
    bool right)
{
    float velocity = m_MoveSpeed * deltaTime;

    if (forward)
        m_Position += m_Front * velocity;

    if (backward)
        m_Position -= m_Front * velocity;

    if (left)
        m_Position -= m_Right * velocity;

    if (right)
        m_Position += m_Right * velocity;
}

void Camera::ProcessMouse(float xOffset, float yOffset)
{
    xOffset *= m_MouseSensitivity;
    yOffset *= m_MouseSensitivity;

    m_Yaw += xOffset;
    m_Pitch += yOffset;

    // Prevent camera flip
    if (m_Pitch > 89.0f)
        m_Pitch = 89.0f;

    if (m_Pitch < -89.0f)
        m_Pitch = -89.0f;

    UpdateCameraVectors();
}

void Camera::UpdateCameraVectors()
{
    glm::vec3 front;

    front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    front.y = sin(glm::radians(m_Pitch));
    front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));

    m_Front = glm::normalize(front);

    m_Right = glm::normalize(
        glm::cross(
            m_Front,
            glm::vec3(0.0f, 1.0f, 0.0f)
        )
    );

    m_Up = glm::normalize(
        glm::cross(
            m_Right,
            m_Front
        )
    );
}