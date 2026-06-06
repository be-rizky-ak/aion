#include "Window.h"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Window::Window(
    int width,
    int height,
    const std::string& title)
{
    if (!glfwInit())
    {
        std::cout
            << "Failed to initialize GLFW\n";

        return;
    }

    glfwWindowHint(
        GLFW_CONTEXT_VERSION_MAJOR,
        3
    );

    glfwWindowHint(
        GLFW_CONTEXT_VERSION_MINOR,
        3
    );

    glfwWindowHint(
        GLFW_OPENGL_PROFILE,
        GLFW_OPENGL_CORE_PROFILE
    );

    m_window =
        glfwCreateWindow(
            width,
            height,
            title.c_str(),
            nullptr,
            nullptr
        );

    if (!m_window)
    {
        std::cout
            << "Failed to create window\n";

        glfwTerminate();

        return;
    }

    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader(
        (GLADloadproc)glfwGetProcAddress))
    {
        std::cout
            << "Failed to initialize GLAD\n";

        return;
    }

    glViewport(
        0,
        0,
        width,
        height
    );
}

Window::~Window()
{
    glfwTerminate();
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(
        m_window
    );
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(
        m_window
    );
}

void Window::PollEvents()
{
    glfwPollEvents();
}

GLFWwindow* Window::GetNativeWindow() const
{
    return m_window;
}