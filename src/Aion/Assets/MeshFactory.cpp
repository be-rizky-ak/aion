#include "MeshFactory.h"

#include <vector>

Mesh* MeshFactory::CreateCube()
{
    std::vector<Vertex> vertices = {{{-0.5f, -0.5f, 0.5f}, {0, 0, 1}, {0, 0}},
                                    {{0.5f, -0.5f, 0.5f}, {0, 0, 1}, {1, 0}},
                                    {{0.5f, 0.5f, 0.5f}, {0, 0, 1}, {1, 1}},
                                    {{-0.5f, 0.5f, 0.5f}, {0, 0, 1}, {0, 1}}};

    std::vector<uint32_t> indices = {0, 1, 2, 2, 3, 0};

    return new Mesh(vertices, indices);
}