#include "Transform.h"

namespace Aion
{
    Transform::Transform() : Position(0.0f), Rotation(Quaternion::Identity()), Scale(1.0f) {}

    Matrix4 Transform::GetMatrix() const
    {
        return Matrix4::Translate(Position) * Matrix4::Rotate(Rotation) * Matrix4::Scale(Scale);
    }
} // namespace Aion