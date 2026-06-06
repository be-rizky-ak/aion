#pragma once

#include "Camera.h"

class PerspectiveCamera : public Camera
{
public:

    PerspectiveCamera(
        float fov,
        float aspect,
        float nearPlane,
        float farPlane
    );
};