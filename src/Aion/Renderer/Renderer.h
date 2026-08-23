#pragma once

#include <cstdint>

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
        void RenderObject(Object3D* object, CameraComponent* camera);
    };
} // namespace Aion