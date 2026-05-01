#include "Application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Aion/Renderer/Renderer.h"

Application::Application()
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW\n";
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(800, 600, "Aion Engine", nullptr, nullptr);
    glfwMakeContextCurrent(m_Window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        return;
    }

    glViewport(0, 0, 800, 600);
}

Application::~Application()
{
    glfwTerminate();
}

void Application::Run()
{
    Renderer renderer;
    renderer.Init();

    while (!glfwWindowShouldClose(m_Window))
    {
        // Input
        if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(m_Window, true);

        renderer.Draw();

        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }

    renderer.Shutdown();
}