#include "MeshFactory.h"
#include <cmath>
#include <glm/gtc/constants.hpp>
#include <vector>

#include "Aion/Math/Math.h"

namespace Aion
{
    Mesh* MeshFactory::CreateCube()
    {
        std::vector<Vertex> vertices = {// Front face (Z+)
            {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
            {{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
            {{0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
            {{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},

            // Back face (Z-)
            {{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
            {{-0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
            {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},

            // Top face (Y+)
            {{-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
            {{0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
            {{0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
            {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},

            // Bottom face (Y-)
            {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
            {{0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
            {{0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
            {{-0.5f, -0.5f, 0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},

            // Right face (X+)
            {{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
            {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
            {{0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
            {{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},

            // Left face (X-)
            {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
            {{-0.5f, -0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
            {{-0.5f, 0.5f, 0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
            {{-0.5f, 0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}}};

        std::vector<uint32_t> indices;
        for (uint32_t i = 0; i < 6; ++i)
        {
            uint32_t offset = i * 4;
            indices.push_back(offset + 0);
            indices.push_back(offset + 1);
            indices.push_back(offset + 2);
            indices.push_back(offset + 2);
            indices.push_back(offset + 3);
            indices.push_back(offset + 0);
        }

        return new Mesh(vertices, indices);
    }

    Mesh* MeshFactory::CreatePlane(float size)
    {
        float half = size * 0.5f;
        std::vector<Vertex> vertices = {{{-half, 0.0f, half}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
            {{half, 0.0f, half}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
            {{half, 0.0f, -half}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
            {{-half, 0.0f, -half}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}}};

        std::vector<uint32_t> indices = {0, 1, 2, 2, 3, 0};
        return new Mesh(vertices, indices);
    }

    Mesh* MeshFactory::CreateSphere(float radius, uint32_t rings, uint32_t sectors)
    {
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;

        float const R = 1.0f / static_cast<float>(rings - 1);
        float const S = 1.0f / static_cast<float>(sectors - 1);

        for (uint32_t r = 0; r < rings; ++r)
        {
            for (uint32_t s = 0; s < sectors; ++s)
            {
                float const phi = -Math::HalfPi() + Math::Pi() * r * R;
                float const theta = Math::TwoPi() * s * S;

                float const y = Math::Sin(phi);
                float const x = Math::Cos(theta) * Math::Cos(phi);
                float const z = Math::Sin(theta) * Math::Cos(phi);

                Vertex v;
                v.Position = Vector3(x, y, z) * radius;
                v.Normal = Vector3(x, y, z);
                v.UV = Vector2(s * S, r * R);
                vertices.push_back(v);
            }
        }

        for (uint32_t r = 0; r < rings - 1; ++r)
        {
            for (uint32_t s = 0; s < sectors - 1; ++s)
            {
                indices.push_back(r * sectors + s);
                indices.push_back(r * sectors + (s + 1));
                indices.push_back((r + 1) * sectors + (s + 1));

                indices.push_back(r * sectors + s);
                indices.push_back((r + 1) * sectors + (s + 1));
                indices.push_back((r + 1) * sectors + s);
            }
        }

        return new Mesh(vertices, indices);
    }

    Mesh* MeshFactory::CreateCapsule(float radius, float height, uint32_t rings, uint32_t sectors)
    {
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;

        float halfHeight = height * 0.5f;
        float const R = 1.0f / (float)(rings - 1);
        float const S = 1.0f / (float)(sectors - 1);

        for (uint32_t r = 0; r < rings; ++r)
        {
            for (uint32_t s = 0; s < sectors; ++s)
            {
                float const y = std::sin(-Math::HalfPi() + Math::Pi() * r * R);
                float const x = std::cos(2 * Math::Pi() * s * S) * std::sin(Math::Pi() * r * R);
                float const z = std::sin(2 * Math::Pi() * s * S) * std::sin(Math::Pi() * r * R);

                Vector3 pos = Vector3(x, y, z) * radius;
                pos.y += (y >= 0.0f) ? halfHeight : -halfHeight;

                Vertex v;
                v.Position = pos;
                v.Normal = Normalize(Vector3(x, y, z));
                v.UV = Vector2(s * S, r * R);
                vertices.push_back(v);
            }
        }

        for (uint32_t r = 0; r < rings - 1; ++r)
        {
            for (uint32_t s = 0; s < sectors - 1; ++s)
            {
                indices.push_back(r * sectors + s);
                indices.push_back(r * sectors + (s + 1));
                indices.push_back((r + 1) * sectors + (s + 1));

                indices.push_back(r * sectors + s);
                indices.push_back((r + 1) * sectors + (s + 1));
                indices.push_back((r + 1) * sectors + s);
            }
        }

        return new Mesh(vertices, indices);
    }
} // namespace Aion