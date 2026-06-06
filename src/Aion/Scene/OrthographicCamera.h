#pragma once

#include "Camera.h"

class OrthographicCamera : public Camera
{
public:

    OrthographicCamera(
        float left,
        float right,
        float bottom,
        float top,
        float nearPlane,
        float farPlane
    );

    glm::mat4 GetProjectionMatrix() const override;

private:

    float m_left;
    float m_right;
    float m_bottom;
    float m_top;
};