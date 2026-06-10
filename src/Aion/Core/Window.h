#pragma once

#include <functional>
#include <string>

struct GLFWwindow;
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

    GLFWwindow* GetNativeWindow() const;

    void SetEventCallback(const EventCallbackFn& callback);
    void SetVSync(bool enabled);

  private:
    GLFWwindow* m_window;
    EventCallbackFn m_eventCallback;
};