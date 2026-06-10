#pragma once

#include <cstdint>

class Scene;
class Camera;
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

    Shader* GetDefaultShader() const;

  private:
    void RenderObject(Object3D* object, Camera* camera);

    Shader* m_defaultShader;
};