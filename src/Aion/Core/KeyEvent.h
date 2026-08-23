#pragma once

#include "Event.h"
#include "KeyCodes.h"

namespace Aion
{
    class KeyPressedEvent : public Event
    {
    public:
        KeyPressedEvent(KeyCode key) : Key(key) {}

        EventType GetType() const override { return EventType::KeyPressed; }

        KeyCode Key;
    };

    class KeyReleasedEvent : public Event
    {
    public:
        KeyReleasedEvent(KeyCode key) : Key(key) {}

        EventType GetType() const override { return EventType::KeyReleased; }

        KeyCode Key;
    };
} // namespace Aion