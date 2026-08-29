#pragma once

#include <memory>

#include "Component.h"

namespace Aion
{
    class Mesh;
    class Material;

    class MeshRenderer : public Component
    {
    public:
        MeshRenderer(
            std::shared_ptr<Mesh> mesh = nullptr, std::shared_ptr<Material> material = nullptr);
        virtual ~MeshRenderer() override = default;

        void SetMesh(std::shared_ptr<Mesh> mesh);
        std::shared_ptr<Mesh> GetMesh() const;

        void SetMaterial(std::shared_ptr<Material> material);
        std::shared_ptr<Material> GetMaterial() const;

    private:
        std::shared_ptr<Mesh> m_mesh;
        std::shared_ptr<Material> m_material;
    };
} // namespace Aion