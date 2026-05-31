#include "Mesh.h"

#include <glad/glad.h>

Mesh::Mesh( const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
{
    m_IndexCount = (unsigned int)indices.size();

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    // VBO

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(Vertex),
        vertices.data(),
        GL_STATIC_DRAW
    );

    // EBO

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        indices.size() * sizeof(uint32_t),
        indices.data(),
        GL_STATIC_DRAW
    );

    // Position

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (void*)offsetof(Vertex, Position)
    );
    glEnableVertexAttribArray(0);

    // Normal

    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (void*)offsetof(Vertex, Normal)
    );
    glEnableVertexAttribArray(1);

    // UV

    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        (void*)offsetof(Vertex, UV)
    );
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Mesh::Draw() const
{
    glBindVertexArray(m_VAO);

    glDrawElements(
        GL_TRIANGLES,
        m_IndexCount,
        GL_UNSIGNED_INT,
        nullptr
    );
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}