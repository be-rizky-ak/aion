#pragma once

#include "Aion/Core/Application.h"

class Object3D;
class Shader;
class PerspectiveCamera;

class SandboxApplication : public Application
{
  public:
    SandboxApplication();
    ~SandboxApplication();

    virtual void OnCreate() override;
    virtual void OnUpdate() override;

  private:
    Object3D* m_CameraObject = nullptr;
    PerspectiveCamera* m_Camera = nullptr;
};