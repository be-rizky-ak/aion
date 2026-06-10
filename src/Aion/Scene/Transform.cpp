#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>

Transform::Transform() : Position(0.0f, 0.0f, 0.0f), Rotation(0.0f, 0.0f, 0.0f), Scale(1.0f, 1.0f, 1.0f)
{
}

glm::mat4 Transform::GetMatrix() const
{
    glm::mat4 matrix = glm::mat4(1.0f);

    // Translation
    matrix = glm::translate(matrix, Position);

    // Rotation X
    matrix = glm::rotate(matrix, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));

    // Rotation Y
    matrix = glm::rotate(matrix, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));

    // Rotation Z
    matrix = glm::rotate(matrix, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    // Scale
    matrix = glm::scale(matrix, Scale);

    return matrix;
}