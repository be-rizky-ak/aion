#include "CameraControllerComponent.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "../Core/Event.h"
#include "../Core/Input.h"
#include "../Core/KeyEvent.h"
#include "../Core/MouseEvent.h"
#include "../Core/Time.h"

#include "Aion/Math/Math.h"

#include "Camera.h"
#include "Object3D.h"

namespace Aion
{
    CameraControllerComponent::CameraControllerComponent()
    {
        m_moveSpeed = 5.0f;
        m_mouseSensitivity = 0.1f;

        m_yaw = 0.0f;
        m_pitch = 0.0f;

        m_forward = false;
        m_backward = false;
        m_left = false;
        m_right = false;

        m_rotating = false;
        m_firstMouse = false;
    }

    void CameraControllerComponent::OnUpdate(float deltaTime)
    {
        Transform& transform = GetOwner()->Transform;

        float yawRad = Math::Radians(m_yaw);
        float pitchRad = Math::Radians(m_pitch);

        Vector3 forward(std::sin(yawRad) * std::cos(pitchRad), std::sin(pitchRad),
                        -std::cos(yawRad) * std::cos(pitchRad));

        forward = Normalize(forward);

        Vector3 worldUp(0.0f, 1.0f, 0.0f);
        Vector3 right = Normalize(Cross(forward, worldUp));

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
        case EventType::KeyPressed:
        {
            auto& keyEvent = static_cast<KeyPressedEvent&>(event);

            switch (keyEvent.Key)
            {
            case Key::W:
                m_forward = true;
                break;
            case Key::S:
                m_backward = true;
                break;
            case Key::A:
                m_left = true;
                break;
            case Key::D:
                m_right = true;
                break;
            }
            break;
        }

        case EventType::KeyReleased:
        {
            auto& keyEvent = static_cast<KeyReleasedEvent&>(event);

            switch (keyEvent.Key)
            {
            case Key::W:
                m_forward = false;
                break;
            case Key::S:
                m_backward = false;
                break;
            case Key::A:
                m_left = false;
                break;
            case Key::D:
                m_right = false;
                break;
            }
            break;
        }

        case EventType::MouseButtonPressed:
        {
            auto& mouseEvent = static_cast<MouseButtonPressedEvent&>(event);

            if (mouseEvent.Button == Mouse::ButtonLeft)
            {
                m_rotating = true;
                m_firstMouse = true;
            }
            break;
        }

        case EventType::MouseButtonReleased:
        {
            auto& mouseEvent = static_cast<MouseButtonReleasedEvent&>(event);

            if (mouseEvent.Button == Mouse::ButtonLeft)
            {
                m_rotating = false;
            }
            break;
        }

        case EventType::MouseMoved:
        {
            MouseMovedEvent& mouseEvent = static_cast<MouseMovedEvent&>(event);

            if (m_rotating)
            {
                if (m_firstMouse)
                {
                    m_lastMouseX = mouseEvent.X;
                    m_lastMouseY = mouseEvent.Y;
                    m_firstMouse = false;
                }

                float deltaX = mouseEvent.X - m_lastMouseX;
                float deltaY = mouseEvent.Y - m_lastMouseY;

                m_yaw += deltaX * m_mouseSensitivity;
                m_pitch -= deltaY * m_mouseSensitivity;
                m_pitch = Math::Clamp(m_pitch, -89.0f, 89.0f);

                m_lastMouseX = mouseEvent.X;
                m_lastMouseY = mouseEvent.Y;
            }
            break;
        }
        }
    }
} // namespace Aion