#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Renderer
{
public:
    void Init();
    void Draw();
    void Shutdown();

    void Update(float deltaTime, GLFWwindow* window);
};