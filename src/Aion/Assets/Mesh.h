#pragma once

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include <glm/glm.hpp>
#include <memory>
#include <vector>

#include "Aion/Math/Vector2.h"
#include "Aion/Math/Vector3.h"

namespace Aion
{
    struct Vertex
    {
        Vector3 Position;
        Vector3 Normal;
        Vector2 UV;
    };

    class Mesh
    {
    public:
        Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
        ~Mesh();

        void Draw() const;

    private:
        uint32_t m_VAO;
        std::unique_ptr<VertexBuffer> m_VBO;
        std::unique_ptr<IndexBuffer> m_EBO;
    };
} // namespace Aion