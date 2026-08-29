#include "CameraComponent.h"

#include "Object3D.h"

namespace Aion
{
    Matrix4 CameraComponent::GetViewMatrix() const
    {
        return Matrix4::Inverse(GetOwner()->GetWorldMatrix());
    }

    Matrix4 CameraComponent::GetProjectionMatrix() const
    {
        return m_camera ? m_camera->GetProjectionMatrix() : Matrix4(1.0f);
    }

    Vector3 CameraComponent::GetPosition() const
    {
        if (GetOwner())
        {
            Vector4 worldMatrixCol = GetOwner()->GetWorldMatrix()[3];
            return Vector3(worldMatrixCol.x, worldMatrixCol.y, worldMatrixCol.z);
        }
        return Vector3(0.0f);
    }
} // namespace Aion