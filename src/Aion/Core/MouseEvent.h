#pragma once

#include "Event.h"
#include "MouseCodes.h"

namespace Aion
{
    class MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(float x, float y) : X(x), Y(y) {}

        EventType GetType() const override { return EventType::MouseMoved; }

        float X;
        float Y;
    };

    class MouseButtonPressedEvent : public Event
    {
    public:
        MouseButtonPressedEvent(MouseCode button) : Button(button) {}

        EventType GetType() const override { return EventType::MouseButtonPressed; }

        MouseCode Button;
    };

    class MouseButtonReleasedEvent : public Event
    {
    public:
        MouseButtonReleasedEvent(MouseCode button) : Button(button) {}

        EventType GetType() const override { return EventType::MouseButtonReleased; }

        MouseCode Button;
    };
} // namespace Aion