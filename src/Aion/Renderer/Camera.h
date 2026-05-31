#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
    Camera(float fov, float aspect, float nearClip, float farClip);

    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;

     void ProcessKeyboard(
        float deltaTime,
        bool forward,
        bool backward,
        bool left,
        bool right
    );

    void ProcessMouse(float xOffset, float yOffset);

private:
    void UpdateCameraVectors();

private:
    float m_FOV;
    float m_Aspect;
    float m_Near;
    float m_Far;

    glm::vec3 m_Position;

    // Direction vectors
    glm::vec3 m_Front;
    glm::vec3 m_Up;
    glm::vec3 m_Right;

    // Rotation
    float m_Yaw;
    float m_Pitch;

    // Movement settings
    float m_MoveSpeed;
    float m_MouseSensitivity;
};