#include "Application.h"

#include "../Renderer/Renderer.h"
#include "../Scene/Camera.h"
#include "../Scene/Scene.h"
#include "Event.h"
#include "Input.h"
#include "Time.h"
#include "Window.h"
#include "WindowEvent.h"

Application::Application()
{
    Application({"Aion Engine", 1280, 720, true});
}

Application::Application(const ApplicationSpecification& spec) : m_specification(spec)
{
    m_window = new Window(m_specification.Width, m_specification.Height, m_specification.Name);

    m_window->SetVSync(m_specification.VSync);

    Input::Initialize(m_window->GetNativeWindow());

    m_window->SetEventCallback([this](Event& event) { OnEvent(event); });

    m_renderer = new Renderer();

    m_renderer->Init();

    m_scene = new Scene();

    m_running = true;
}

Application::~Application()
{
    delete m_scene;

    m_renderer->Shutdown();
    delete m_renderer;

    delete m_window;
}

void Application::Run()
{
    OnCreate();

    m_scene->Start();

    while (m_running && !m_window->ShouldClose())
    {
        Time::Update();

        Input::Update();

        float dt = Time::GetDeltaTime();

        m_scene->Update(dt);

        OnUpdate();

        OnRender();

        m_window->SwapBuffers();
        m_window->PollEvents();
    }

    OnDestroy();
}

void Application::OnCreate()
{
}

void Application::OnUpdate()
{
}

void Application::OnRender()
{
}

void Application::OnEvent(Event& event)
{
    switch (event.GetType())
    {
    case EventType::WindowClose: {
        m_running = false;
        break;
    }

    case EventType::WindowResize: {
        WindowResizeEvent& resizeEvent = static_cast<WindowResizeEvent&>(event);

        int width = resizeEvent.GetWidth();
        int height = resizeEvent.GetHeight();
        if (height == 0)
            height = 1;

        m_renderer->OnResize(width, height);

        Camera* camera = m_scene->GetActiveCamera();
        if (camera)
        {
            camera->SetAspect((float)width / (float)height);
        }

        break;
    }
    }

    if (m_scene)
    {
        m_scene->OnEvent(event);
    }
}

void Application::OnDestroy()
{
}