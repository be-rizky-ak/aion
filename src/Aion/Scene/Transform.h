#pragma once

#include <glm/glm.hpp>

class Transform
{
  public:
    Transform();

    glm::mat4 GetMatrix() const;

  public:
    glm::vec3 Position;
    glm::vec3 Rotation;
    glm::vec3 Scale;
};