#pragma once

#include <memory>
#include <vector>

#include "Aion/Math/Matrix4.h"
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

        void SetJointMatrices(const std::vector<Matrix4>& matrices) { m_JointMatrices = matrices; }
        const std::vector<Matrix4>& GetJointMatrices() const { return m_JointMatrices; }

    private:
        std::shared_ptr<Mesh> m_mesh;
        std::shared_ptr<Material> m_material;
        std::vector<Matrix4> m_JointMatrices;
    };
} // namespace Aion