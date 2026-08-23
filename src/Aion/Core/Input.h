#pragma once

#include "KeyCodes.h"
#include "MouseCodes.h"

struct GLFWwindow;

namespace Aion
{
    class Input
    {
    public:
        static void Initialize(GLFWwindow* window);

        static bool GetKey(KeyCode key);

        static bool GetMouseButton(MouseCode button);

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
} // namespace Aion