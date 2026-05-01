#pragma once

struct GLFWwindow;

class Application
{
public:
    Application();
    ~Application();

    void Run();

private:
    GLFWwindow* m_Window;
};