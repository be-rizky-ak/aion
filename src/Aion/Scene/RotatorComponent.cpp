#include "RotatorComponent.h"
#include "Object3D.h"

namespace Aion
{
    void RotatorComponent::OnUpdate(float deltaTime)
    {
        Vector3 eulerDelta = Speed * deltaTime;
        Quaternion deltaRotation = Quaternion::FromEuler(eulerDelta.x, eulerDelta.y, eulerDelta.z);

        GetOwner()->Transform.Rotation = GetOwner()->Transform.Rotation * deltaRotation;
    }
} // namespace Aion