#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Aion/Math/Matrix4.h"
#include "Aion/Math/Quaternion.h"
#include "Aion/Math/Vector3.h"

namespace Aion
{
    class Mesh;
    class Material;
    class Texture;

    struct ModelPrimitive
    {
        std::shared_ptr<Mesh> MeshPtr;
        std::shared_ptr<Material> MaterialPtr;
    };

    struct ModelNode
    {
        std::string Name;

        Vector3 Translation{0.0f};
        Quaternion Rotation = Quaternion::Identity();
        Vector3 Scale{1.0f};

        Matrix4 LocalMatrix = Matrix4::Identity();

        std::vector<ModelPrimitive> Primitives;
        std::vector<std::shared_ptr<ModelNode>> Children;
    };

    class Model
    {
    public:
        explicit Model(const std::string& path);
        ~Model() = default;

        const std::vector<std::shared_ptr<Texture>>& GetTextures() const { return m_textures; }
        const std::vector<std::shared_ptr<Material>>& GetMaterials() const { return m_materials; }
        const std::vector<std::shared_ptr<ModelNode>>& GetRootNodes() const { return m_rootNodes; }

    private:
        std::vector<std::shared_ptr<ModelNode>> m_rootNodes;
        std::vector<std::shared_ptr<Texture>> m_textures;
        std::vector<std::shared_ptr<Material>> m_materials;
    };
} // namespace Aion