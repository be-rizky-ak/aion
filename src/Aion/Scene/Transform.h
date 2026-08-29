#pragma once

#include "Aion/Math/Math.h"
#include "Aion/Math/Matrix4.h"
#include "Aion/Math/Quaternion.h"
#include "Aion/Math/Vector3.h"

namespace Aion
{
    class Transform
    {
    public:
        Transform();

        Matrix4 GetMatrix() const;

    public:
        Vector3 Position{0.0f};
        Quaternion Rotation = Quaternion::Identity();
        Vector3 Scale{1.0f};
    };
} // namespace Aion