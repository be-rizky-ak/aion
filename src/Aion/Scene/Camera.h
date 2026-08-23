#pragma once

#include "Aion/Math/Math.h"
#include "Aion/Math/Matrix4.h"

namespace Aion
{
    class Camera
    {
    public:
        virtual ~Camera() = default;

        virtual Matrix4 GetProjectionMatrix() const = 0;
        virtual void SetAspect(float aspect) {}
    };
} // namespace Aion