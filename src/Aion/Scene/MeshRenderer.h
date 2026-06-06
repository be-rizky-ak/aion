#pragma once

#include "../Assets/Mesh.h"
#include "../Renderer/Material.h"

class Mesh;
class Material;

class MeshRenderer
{
public:

    MeshRenderer(
        Mesh* mesh,
        Material* material
    );

    Mesh* GetMesh() const;
    Material* GetMaterial() const;

private:

    Mesh* m_Mesh;
    Material* m_Material;
};