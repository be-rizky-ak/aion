#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "Camera.h"
#include "Component.h"

namespace Aion
{
    class CameraComponent : public Component
    {
    public:
        CameraComponent(std::unique_ptr<Camera> camera) : m_camera(std::move(camera)) {}

        Camera* GetCamera() const { return m_camera.get(); }
        void SetCamera(std::unique_ptr<Camera> camera) { m_camera = std::move(camera); }

        Matrix4 GetViewMatrix() const;
        Matrix4 GetProjectionMatrix() const;
        Vector3 GetPosition() const;

    private:
        std::unique_ptr<Camera> m_camera;
    };
} // namespace Aion