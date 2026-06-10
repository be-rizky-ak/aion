#pragma once

#include <cstdint>

class Time
{
  public:
    static void Update();

    static float GetTime();
    static float GetDeltaTime();
    static float GetFPS();
    static uint64_t GetFrameCount();

  private:
    static float s_time;
    static float s_deltaTime;
    static float s_lastTime;
    static uint64_t s_frameCount;
};