#pragma once

#include "Aion/Math/Vector3.h"
#include "Component.h"

namespace Aion
{
    class RotatorComponent : public Component
    {
    public:
        Vector3 Speed = {0.0f, 90.0f, 0.0f};

        void OnUpdate(float deltaTime) override;
    };
} // namespace Aion