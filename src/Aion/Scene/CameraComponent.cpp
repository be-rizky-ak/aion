#include "CameraComponent.h"

CameraComponent::CameraComponent()
{
}

CameraComponent::CameraComponent(Camera* camera) : m_camera(camera)
{
}

CameraComponent::~CameraComponent()
{
}

Camera* CameraComponent::GetCamera() const
{
    return m_camera;
}