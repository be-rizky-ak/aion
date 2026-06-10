#pragma once

struct GLFWwindow;

class Input
{
  public:
    static void Initialize(GLFWwindow* window);

    static bool GetKey(int key);

    static bool GetMouseButton(int button);

    static float GetMouseX();
    static float GetMouseY();

    static float GetMouseDeltaX();
    static float GetMouseDeltaY();

    static void Update();

  private:
    static GLFWwindow* s_window;

    static float s_mouseX;
    static float s_mouseY;

    static float s_lastMouseX;
    static float s_lastMouseY;

    static float s_mouseDeltaX;
    static float s_mouseDeltaY;
};