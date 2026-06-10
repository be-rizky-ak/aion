#pragma once

#include "Event.h"

class MouseMovedEvent : public Event
{
  public:
    MouseMovedEvent(float x, float y) : X(x), Y(y)
    {
    }

    EventType GetType() const override
    {
        return EventType::MouseMoved;
    }

    float X;
    float Y;
};

class MouseButtonPressedEvent : public Event
{
  public:
    MouseButtonPressedEvent(int button) : Button(button)
    {
    }

    EventType GetType() const override
    {
        return EventType::MouseButtonPressed;
    }

    int Button;
};

class MouseButtonReleasedEvent : public Event
{
  public:
    MouseButtonReleasedEvent(int button) : Button(button)
    {
    }

    EventType GetType() const override
    {
        return EventType::MouseButtonReleased;
    }

    int Button;
};