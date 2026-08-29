#include "ModelImporter.h"

#include "Aion/Assets/Model.h"
#include "Aion/Scene/MeshRenderer.h"
#include "Aion/Scene/ModelComponent.h"
#include "Aion/Scene/Object3D.h"

namespace Aion
{
    static void BuildSceneTree(Object3D* parent, const std::shared_ptr<ModelNode>& node)
    {
        auto obj = std::make_unique<Object3D>();

        obj->Transform.Position = node->Translation;
        obj->Transform.Rotation = node->Rotation;
        obj->Transform.Scale = node->Scale;

        if (!node->Primitives.empty())
        {
            if (node->Primitives.size() == 1)
            {
                obj->AddComponent<MeshRenderer>(
                    node->Primitives[0].MeshPtr, node->Primitives[0].MaterialPtr);
            }
            else
            {
                for (const auto& primitive : node->Primitives)
                {
                    auto primChild = std::make_unique<Object3D>();
                    primChild->AddComponent<MeshRenderer>(primitive.MeshPtr, primitive.MaterialPtr);
                    obj->AddChild(std::move(primChild));
                }
            }
        }

        for (const auto& childNode : node->Children)
        {
            BuildSceneTree(obj.get(), childNode);
        }

        parent->AddChild(std::move(obj));
    }

    std::shared_ptr<Object3D> ModelImporter::Load(const std::string& path)
    {
        auto model = std::make_shared<Model>(path);
        auto root = std::make_shared<Object3D>();

        for (const auto& rootNode : model->GetRootNodes())
        {
            BuildSceneTree(root.get(), rootNode);
        }

        root->AddComponent<ModelComponent>(model);
        return root;
    }
} // namespace Aion