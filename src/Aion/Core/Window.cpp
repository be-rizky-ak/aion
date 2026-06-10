#include "Window.h"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "KeyEvent.h"
#include "MouseEvent.h"
#include "WindowEvent.h"

Window::Window(int width, int height, const std::string& title)
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW\n";

        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (!m_window)
    {
        std::cout << "Failed to create window\n";

        glfwTerminate();

        return;
    }

    glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
        Window* win = (Window*)glfwGetWindowUserPointer(window);

        WindowCloseEvent event;

        if (win->m_eventCallback)
        {
            win->m_eventCallback(event);
        }
    });

    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
        Window* win = (Window*)glfwGetWindowUserPointer(window);

        WindowResizeEvent event(width, height);

        if (win->m_eventCallback)
        {
            win->m_eventCallback(event);
        }
    });

    glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));

        if (!win)
        {
            return;
        }

        if (action == GLFW_PRESS)
        {
            KeyPressedEvent event(key);

            if (win->m_eventCallback)
            {
                win->m_eventCallback(event);
            }
        }
        else if (action == GLFW_RELEASE)
        {
            KeyReleasedEvent event(key);

            if (win->m_eventCallback)
            {
                win->m_eventCallback(event);
            }
        }
    });

    glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
        Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));

        if (!win)
        {
            return;
        }

        if (action == GLFW_PRESS)
        {
            MouseButtonPressedEvent event(button);

            if (win->m_eventCallback)
            {
                win->m_eventCallback(event);
            }
        }
        else if (action == GLFW_RELEASE)
        {
            MouseButtonReleasedEvent event(button);

            if (win->m_eventCallback)
            {
                win->m_eventCallback(event);
            }
        }
    });

    glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos) {
        Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));

        if (!win)
        {
            return;
        }

        MouseMovedEvent event((float)xpos, (float)ypos);

        if (win->m_eventCallback)
        {
            win->m_eventCallback(event);
        }
    });

    glfwSetWindowUserPointer(m_window, this);

    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";

        return;
    }

    glViewport(0, 0, width, height);
}

Window::~Window()
{
    glfwTerminate();
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(m_window);
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(m_window);
}

void Window::PollEvents()
{
    glfwPollEvents();
}

void Window::SetEventCallback(const EventCallbackFn& callback)
{
    m_eventCallback = callback;
}

GLFWwindow* Window::GetNativeWindow() const
{
    return m_window;
}

void Window::SetVSync(bool enabled)
{
    glfwSwapInterval(enabled ? 1 : 0);
}