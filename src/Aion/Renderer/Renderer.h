#pragma once

class Scene;
class Camera;
class Shader;

class Renderer
{
public:

    Renderer();
    ~Renderer();

    void Init();

    void Render(
        Scene* scene,
        Camera* camera,
        Shader* shader
    );

    void Shutdown();
};