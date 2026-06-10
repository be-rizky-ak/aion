#pragma once

#include <glm/glm.hpp>
#include <vector>

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 UV;
};

class Mesh
{
  public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);

    ~Mesh();

    void Draw() const;

  private:
    unsigned int m_VAO;
    unsigned int m_VBO;
    unsigned int m_EBO;

    unsigned int m_indexCount;
};