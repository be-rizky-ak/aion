#pragma once

#include <glm/glm.hpp>

#include "CameraComponent.h"

class Camera : public CameraComponent
{
  public:
    Camera(float fov, float aspect, float nearClip, float farClip);
    virtual ~Camera() = default;

    void SetAspect(float aspect);

    glm::mat4 GetViewMatrix() const;
    float GetAspect() const;

    virtual glm::mat4 GetProjectionMatrix() const;

  protected:
    float m_fov;
    float m_aspect;
    float m_near;
    float m_far;
};