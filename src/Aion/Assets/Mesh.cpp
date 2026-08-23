#include "Mesh.h"
#include <glad/glad.h>

namespace Aion
{
    Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
    {
        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        // Vertex Buffer
        m_VBO = std::make_unique<VertexBuffer>(vertices.data(),
                                               (uint32_t)(vertices.size() * sizeof(Vertex)));

        // Index Buffer
        m_EBO = std::make_unique<IndexBuffer>(indices.data(), (uint32_t)indices.size());

        // Position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              (void*)offsetof(Vertex, Position));
        glEnableVertexAttribArray(0);

        // Normal
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              (void*)offsetof(Vertex, Normal));
        glEnableVertexAttribArray(1);

        // UV
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              (void*)offsetof(Vertex, UV));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);
    }

    Mesh::~Mesh()
    {
        glDeleteVertexArrays(1, &m_VAO);
    }

    void Mesh::Draw() const
    {
        glBindVertexArray(m_VAO);
        glDrawElements(GL_TRIANGLES, m_EBO->GetCount(), GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }
} // namespace Aion