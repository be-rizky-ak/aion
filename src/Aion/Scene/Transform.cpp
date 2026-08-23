#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Aion
{
    Transform::Transform()
        : Position(0.0f, 0.0f, 0.0f), Rotation(0.0f, 0.0f, 0.0f), Scale(1.0f, 1.0f, 1.0f)
    {
    }

    Matrix4 Transform::GetMatrix() const
    {

        // Translation
        Matrix4 translation = Matrix4::Translate(Position);

        Matrix4 rotX = Matrix4::Rotate(Math::Radians(Rotation.x), Vector3(1.0f, 0.0f, 0.0f));
        Matrix4 rotY = Matrix4::Rotate(Math::Radians(Rotation.y), Vector3(0.0f, 1.0f, 0.0f));
        Matrix4 rotZ = Matrix4::Rotate(Math::Radians(Rotation.z), Vector3(0.0f, 0.0f, 1.0f));

        Matrix4 rotation = rotZ * rotY * rotX;

        Matrix4 scale = Matrix4::Scale(Scale);

        return translation * rotation * scale;
    }
} // namespace Aion