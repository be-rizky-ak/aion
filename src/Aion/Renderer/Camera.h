#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
    Camera(float fov, float aspect, float nearClip, float farClip);

    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;

private:
    float m_FOV;
    float m_Aspect;
    float m_Near;
    float m_Far;

    glm::vec3 m_Position;
};