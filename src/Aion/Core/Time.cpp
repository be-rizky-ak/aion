#include "Time.h"

#include <GLFW/glfw3.h>

float Time::s_time = 0.0f;
float Time::s_deltaTime = 0.0f;
float Time::s_lastTime = 0.0f;
uint64_t Time::s_frameCount = 0;

void Time::Update()
{
    float currentTime = (float)glfwGetTime();

    if (s_frameCount == 0)
    {
        s_lastTime = currentTime;
    }

    s_deltaTime = currentTime - s_lastTime;

    s_time = currentTime;

    s_lastTime = currentTime;

    s_frameCount++;
}

float Time::GetTime()
{
    return s_time;
}

float Time::GetDeltaTime()
{
    return s_deltaTime;
}

uint64_t Time::GetFrameCount()
{
    return s_frameCount;
}

float Time::GetFPS()
{
    if (s_deltaTime <= 0.0f)
    {
        return 0.0f;
    }

    return 1.0f / s_deltaTime;
}