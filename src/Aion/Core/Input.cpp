#include "Input.h"

#include <GLFW/glfw3.h>

GLFWwindow* Input::s_window = nullptr;

float Input::s_mouseX = 0.0f;
float Input::s_mouseY = 0.0f;

float Input::s_lastMouseX = 0.0f;
float Input::s_lastMouseY = 0.0f;

float Input::s_mouseDeltaX = 0.0f;
float Input::s_mouseDeltaY = 0.0f;

void Input::Initialize(GLFWwindow* window)
{
    s_window = window;
}

bool Input::GetKey(int key)
{
    if (!s_window)
    {
        return false;
    }

    return glfwGetKey(s_window, key) == GLFW_PRESS;
}

bool Input::GetMouseButton(int button)
{
    if (!s_window)
    {
        return false;
    }

    return glfwGetMouseButton(s_window, button) == GLFW_PRESS;
}

float Input::GetMouseX()
{
    return s_mouseX;
}

float Input::GetMouseY()
{
    return s_mouseY;
}

float Input::GetMouseDeltaX()
{
    return s_mouseDeltaX;
}

float Input::GetMouseDeltaY()
{
    return s_mouseDeltaY;
}

void Input::Update()
{
    if (!s_window)
    {
        return;
    }

    double x;
    double y;

    glfwGetCursorPos(s_window, &x, &y);

    s_mouseX = (float)x;
    s_mouseY = (float)y;

    s_mouseDeltaX = s_mouseX - s_lastMouseX;

    s_mouseDeltaY = s_mouseY - s_lastMouseY;

    s_lastMouseX = s_mouseX;

    s_lastMouseY = s_mouseY;
}