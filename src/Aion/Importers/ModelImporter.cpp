#include "ModelImporter.h"

#include "../Assets/Model.h"
#include "../Scene/MeshRenderer.h"
#include "../Scene/ModelComponent.h"
#include "../Scene/Object3D.h"

Object3D* ModelImporter::Load(const std::string& path)
{
    Model* model = new Model(path);

    Object3D* root = new Object3D();

    const auto& primitives = model->GetPrimitives();

    for (const auto& primitive : primitives)
    {
        Object3D* child = new Object3D();

        child->AddComponent<MeshRenderer>(primitive.Mesh, primitive.Material);

        root->AddChild(child);
    }

    root->AddComponent<ModelComponent>(model);

    return root;
}