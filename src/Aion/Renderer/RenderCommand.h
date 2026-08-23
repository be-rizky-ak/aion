#pragma once

#include "RenderState.h"

namespace Aion
{

    class RenderCommand
    {
    public:
        static void Init();
        static void ApplyState(const RenderState& state);

    private:
        static RenderState s_CurrentState;
        static bool s_Initialized;
    };

} // namespace Aion