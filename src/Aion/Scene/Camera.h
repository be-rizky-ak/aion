#pragma once

#include <glm/glm.hpp>

#include "../Scene/Object3D.h"

class Camera : public Object3D
{
public:
    Camera(float fov, float aspect, float nearClip, float farClip);

    glm::mat4 GetViewMatrix() const;
    
    virtual glm::mat4 GetProjectionMatrix() const;

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

protected:
    float m_fov;
    float m_aspect;
    float m_near;
    float m_far;

private:
    // Direction vectors
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;

    // Rotation
    float m_yaw;
    float m_pitch;

    // Movement settings
    float m_moveSpeed;
    float m_mouseSensitivity;
};