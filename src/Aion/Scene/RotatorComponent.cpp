#include "RotatorComponent.h"

#include "Object3D.h"

namespace Aion
{
    void RotatorComponent::OnUpdate(float deltaTime)
    {
        GetTransform().Rotation += Speed * deltaTime;
    }
} // namespace Aion