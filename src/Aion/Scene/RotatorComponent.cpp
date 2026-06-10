#include "RotatorComponent.h"

#include "Object3D.h"

void RotatorComponent::OnUpdate(float deltaTime)
{
    GetTransform().Rotation += Speed * deltaTime;
}