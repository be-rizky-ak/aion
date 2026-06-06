#include "PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(
    float fov,
    float aspect,
    float nearPlane,
    float farPlane)
    :
    Camera(
        fov,
        aspect,
        nearPlane,
        farPlane
    )
{
}