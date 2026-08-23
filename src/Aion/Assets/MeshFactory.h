#pragma once

#include "Mesh.h"

namespace Aion
{
    class MeshFactory
    {
    public:
        static Mesh* CreateCube();
        static Mesh* CreatePlane(float size = 1.0f);
        static Mesh* CreateSphere(float radius = 0.5f, uint32_t rings = 16, uint32_t sectors = 32);
        static Mesh* CreateCapsule(
            float radius = 0.5f, float height = 1.0f, uint32_t rings = 8, uint32_t sectors = 16);
    };
} // namespace Aion