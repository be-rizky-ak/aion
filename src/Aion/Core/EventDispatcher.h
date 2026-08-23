#pragma once

#include "Event.h"

namespace Aion
{
    class EventDispatcher
    {
    public:
        template <typename T, typename F> static bool Dispatch(Event& event, F&& callback)
        {
            if (event.GetType() == T().GetType())
            {
                event.Handled = callback(static_cast<T&>(event));

                return true;
            }

            return false;
        }
    };
} // namespace Aion