#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include "RenderQueue.h"

namespace Aion
{
    class Scene;
    class CameraComponent;
    class Shader;
    class Object3D;

    class Renderer
    {
    public:
        Renderer();
        ~Renderer();

        void Init();
        void Render(Scene* scene);
        void Shutdown();

        void OnResize(uint32_t width, uint32_t height);

    private:
        void SubmitObject(Object3D* object, CameraComponent* camera);
        void ExecuteCommands(const std::vector<DrawCommand>& commands, CameraComponent* camera);

        RenderQueue m_RenderQueue;
    };
} // namespace Aion