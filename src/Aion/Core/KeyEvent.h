#pragma once

#include "Event.h"

class KeyPressedEvent : public Event
{
  public:
    KeyPressedEvent(int key) : Key(key)
    {
    }

    EventType GetType() const override
    {
        return EventType::KeyPressed;
    }

    int Key;
};

class KeyReleasedEvent : public Event
{
  public:
    KeyReleasedEvent(int key) : Key(key)
    {
    }

    EventType GetType() const override
    {
        return EventType::KeyReleased;
    }

    int Key;
};