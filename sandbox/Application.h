#pragma once

#include "Aion/Core/Window.h"
#include "Aion/Scene/Scene.h"


class Application
{
public:

    Application();

    void Run();

private:

    Scene* m_scene;
    Window m_window;
};