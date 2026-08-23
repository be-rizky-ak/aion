#pragma once

#include "Aion/Math/Math.h"
#include "Aion/Math/Matrix4.h"

namespace Aion
{
    class Transform
    {
    public:
        Transform();

        Matrix4 GetMatrix() const;

    public:
        Vector3 Position;
        Vector3 Rotation;
        Vector3 Scale;
    };
} // namespace Aion