#pragma once

#include "Aion/Core/Application.h"

namespace Aion
{
    class Object3D;
    class Shader;
    class CameraComponent;
    class PerspectiveCamera;
} // namespace Aion

class SandboxApplication : public Aion::Application
{
public:
    SandboxApplication();
    ~SandboxApplication();

    virtual void OnCreate() override;
    virtual void OnUpdate() override;
};