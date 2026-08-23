#pragma once

#include <functional>
#include <string>

struct GLFWwindow;

namespace Aion
{
    class Event;

    class Window
    {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        Window(int width, int height, const std::string& title);
        ~Window();

        bool ShouldClose() const;
        void SwapBuffers();
        void PollEvents();
        void SetFullscreen(bool fullscreen);
        bool IsFullscreen() const { return m_isFullscreen; }

        GLFWwindow* GetNativeWindow() const;

        void SetEventCallback(const EventCallbackFn& callback);
        void SetVSync(bool enabled);

    private:
        GLFWwindow* m_window;
        EventCallbackFn m_eventCallback;

        bool m_isFullscreen = false;
        int m_windowedPosX = 100;
        int m_windowedPosY = 100;
        int m_windowedWidth = 1280;
        int m_windowedHeight = 720;
    };
} // namespace Aion