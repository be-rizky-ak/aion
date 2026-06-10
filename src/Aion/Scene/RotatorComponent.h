#pragma once

#include "Component.h"

#include <glm/glm.hpp>

class RotatorComponent : public Component
{
  public:
    glm::vec3 Speed = {0.0f, 90.0f, 0.0f};

    void OnUpdate(float deltaTime) override;
};