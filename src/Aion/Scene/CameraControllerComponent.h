#pragma once

#include "Component.h"

class Camera;

class CameraControllerComponent : public Component
{
  public:
    CameraControllerComponent();

    void OnUpdate(float deltaTime) override;
    virtual void OnEvent(Event& event) override;

  private:
    float m_moveSpeed;
    float m_mouseSensitivity;

    float m_yaw;
    float m_pitch;

    bool m_forward;
    bool m_backward;
    bool m_left;
    bool m_right;

    bool m_rotating;

    float m_lastMouseX;
    float m_lastMouseY;
};