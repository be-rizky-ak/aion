#pragma once

#include <string>
#include <vector>

#include "Transform.h"

class MeshRenderer;

class Object3D
{
public:

    Object3D();
    virtual ~Object3D();

    Transform Transform;

    std::string Name;

    void SetMeshRenderer(
        MeshRenderer* renderer
    );

    MeshRenderer* GetMeshRenderer() const;

private:
    MeshRenderer* m_meshRenderer;
};