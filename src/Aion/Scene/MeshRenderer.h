#pragma once

#include "Component.h"

class Mesh;
class Material;

class MeshRenderer : public Component
{
  public:
    MeshRenderer(Mesh* mesh, Material* material);

    Mesh* GetMesh() const;
    Material* GetMaterial() const;

  private:
    Mesh* m_mesh;
    Material* m_material;
};