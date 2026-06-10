#include "CameraControllerComponent.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "../Core/Event.h"
#include "../Core/Input.h"
#include "../Core/KeyEvent.h"
#include "../Core/MouseEvent.h"
#include "../Core/Time.h"

#include "Camera.h"
#include "Object3D.h"

CameraControllerComponent::CameraControllerComponent()
{
    m_moveSpeed = 5.0f;
    m_mouseSensitivity = 0.1f;

    m_yaw = -90.0f;
    m_pitch = 0.0f;

    m_forward = false;
    m_backward = false;
    m_left = false;
    m_right = false;

    m_rotating = false;
}

void CameraControllerComponent::OnUpdate(float deltaTime)
{
    Transform& transform = GetOwner()->Transform;

    glm::vec3 forward(cos(glm::radians(m_yaw)), 0.0f, sin(glm::radians(m_yaw)));

    forward = glm::normalize(forward);

    glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0, 1, 0)));

    float speed = m_moveSpeed * deltaTime;

    if (m_forward)
    {
        transform.Position += forward * speed;
    }

    if (m_backward)
    {
        transform.Position -= forward * speed;
    }

    if (m_left)
    {
        transform.Position -= right * speed;
    }

    if (m_right)
    {
        transform.Position += right * speed;
    }

    transform.Rotation.x = m_pitch;

    transform.Rotation.y = m_yaw;
}

void CameraControllerComponent::OnEvent(Event& event)
{
    switch (event.GetType())
    {
    case EventType::KeyPressed: {
        KeyPressedEvent& keyEvent = static_cast<KeyPressedEvent&>(event);

        switch (keyEvent.Key)
        {
        case GLFW_KEY_W:
            m_forward = true;
            break;

        case GLFW_KEY_S:
            m_backward = true;
            break;

        case GLFW_KEY_A:
            m_left = true;
            break;

        case GLFW_KEY_D:
            m_right = true;
            break;
        }

        break;
    }

    case EventType::KeyReleased: {
        KeyReleasedEvent& keyEvent = static_cast<KeyReleasedEvent&>(event);

        switch (keyEvent.Key)
        {
        case GLFW_KEY_W:
            m_forward = false;
            break;

        case GLFW_KEY_S:
            m_backward = false;
            break;

        case GLFW_KEY_A:
            m_left = false;
            break;

        case GLFW_KEY_D:
            m_right = false;
            break;
        }

        break;
    }

    case EventType::MouseButtonPressed: {
        MouseButtonPressedEvent& mouseEvent = static_cast<MouseButtonPressedEvent&>(event);

        if (mouseEvent.Button == GLFW_MOUSE_BUTTON_LEFT)
        {
            m_rotating = true;
        }

        break;
    }

    case EventType::MouseButtonReleased: {
        MouseButtonReleasedEvent& mouseEvent = static_cast<MouseButtonReleasedEvent&>(event);

        if (mouseEvent.Button == GLFW_MOUSE_BUTTON_LEFT)
        {
            m_rotating = false;
        }

        break;
    }

    case EventType::MouseMoved: {
        MouseMovedEvent& mouseEvent = static_cast<MouseMovedEvent&>(event);

        if (m_rotating)
        {
            float deltaX = mouseEvent.X - m_lastMouseX;

            float deltaY = mouseEvent.Y - m_lastMouseY;

            m_yaw += deltaX * m_mouseSensitivity;

            m_pitch -= deltaY * m_mouseSensitivity;

            m_pitch = glm::clamp(m_pitch, -89.0f, 89.0f);
        }

        m_lastMouseX = mouseEvent.X;

        m_lastMouseY = mouseEvent.Y;

        break;
    }
    }
}