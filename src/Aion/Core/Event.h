#pragma once

namespace Aion
{
    enum class EventType
    {
        None = 0,

        WindowClose,
        WindowResize,

        KeyPressed,
        KeyReleased,

        MouseMoved,

        MouseButtonPressed,
        MouseButtonReleased
    };

    class Event
    {
    public:
        virtual ~Event() = default;

        virtual EventType GetType() const = 0;

        bool Handled = false;
    };
} // namespace Aion