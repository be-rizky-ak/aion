#pragma once

#include <string>

struct GLFWwindow;

class Window
{
public:

    Window(
        int width,
        int height,
        const std::string& title
    );

    ~Window();

    bool ShouldClose() const;

    void SwapBuffers();

    void PollEvents();

    GLFWwindow* GetNativeWindow() const;

private:

    GLFWwindow* m_window;
};