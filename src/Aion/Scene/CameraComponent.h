#pragma once

#include <glm/glm.hpp>

#include "Component.h"

class Camera;

class CameraComponent : public Component
{
  public:
    CameraComponent();
    CameraComponent(Camera* camera);

    ~CameraComponent();

    Camera* GetCamera() const;

    virtual glm::mat4 GetViewMatrix() const = 0;
    virtual glm::mat4 GetProjectionMatrix() const = 0;

  private:
    Camera* m_camera;
};