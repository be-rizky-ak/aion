#pragma once

#include "Event.h"

class WindowCloseEvent : public Event
{
  public:
    EventType GetType() const override
    {
        return EventType::WindowClose;
    }
};

class WindowResizeEvent : public Event
{
  public:
    WindowResizeEvent(int width, int height) : m_width(width), m_height(height)
    {
    }

    EventType GetType() const override
    {
        return EventType::WindowResize;
    }

    int GetWidth() const
    {
        return m_width;
    }

    int GetHeight() const
    {
        return m_height;
    }

  private:
    int m_width;
    int m_height;
};