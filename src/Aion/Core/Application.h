#pragma once

#include <memory>
#include <string>

class Window;
class Renderer;
class Scene;
class Event;

struct ApplicationSpecification
{
    std::string Name = "Aion";

    uint32_t Width = 1280;
    uint32_t Height = 720;

    bool VSync = true;
};

class Application
{
  public:
    Application();
    Application(const ApplicationSpecification& spec);
    virtual ~Application();

    void Run();

    virtual void OnCreate();
    virtual void OnUpdate();
    virtual void OnRender();
    virtual void OnEvent(Event& event);
    virtual void OnDestroy();

    Scene* GetScene() const
    {
        return m_scene;
    }
    Renderer* GetRenderer() const
    {
        return m_renderer;
    }
    Window* GetWindow() const
    {
        return m_window;
    }
    const ApplicationSpecification& GetSpecification() const
    {
        return m_specification;
    }

  protected:
    Window* m_window;
    Renderer* m_renderer;
    Scene* m_scene;

    ApplicationSpecification m_specification;

  private:
    bool m_running;
};