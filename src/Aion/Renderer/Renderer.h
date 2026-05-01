#pragma once

class Renderer
{
public:
    void Init();
    void Draw();
    void Shutdown();

private:
    unsigned int VAO, VBO;
};