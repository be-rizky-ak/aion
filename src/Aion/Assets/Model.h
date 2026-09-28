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

    struct Joint
    {
        std::string Name;
        int ParentIndex = -1;
        Matrix4 InverseBindMatrix = Matrix4::Identity();
        int NodeIndex = -1;
    };

    struct AnimationKeyframe
    {
        float Time = 0.0f;
        Vector3 Translation{0.0f};
        Quaternion Rotation = Quaternion::Identity();
        Vector3 Scale{1.0f};
    };

    struct AnimationChannel
    {
        int JointIndex = -1;
        std::string Path;
        std::vector<AnimationKeyframe> Keyframes;
    };

    struct AnimationClip
    {
        std::string Name;
        float Duration = 0.0f;
        std::vector<AnimationChannel> Channels;
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

        std::vector<int> JointIndices;
        int SkinIndex = -1;
    };

    class Model
    {
    public:
        explicit Model(const std::string& path);
        ~Model() = default;

        const std::vector<std::shared_ptr<Texture>>& GetTextures() const { return m_textures; }
        const std::vector<std::shared_ptr<Material>>& GetMaterials() const { return m_materials; }
        const std::vector<std::shared_ptr<ModelNode>>& GetRootNodes() const { return m_rootNodes; }
        const std::vector<Joint>& GetJoints() const { return m_joints; }
        const std::vector<AnimationClip>& GetAnimations() const { return m_animations; }

    private:
        std::vector<std::shared_ptr<ModelNode>> m_rootNodes;
        std::vector<std::shared_ptr<Texture>> m_textures;
        std::vector<std::shared_ptr<Material>> m_materials;
        std::vector<Joint> m_joints;
        std::vector<AnimationClip> m_animations;
    };
} // namespace Aion