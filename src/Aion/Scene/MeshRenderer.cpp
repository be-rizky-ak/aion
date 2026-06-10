#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(Mesh* mesh, Material* material) : m_mesh(mesh), m_material(material)
{
}

Mesh* MeshRenderer::GetMesh() const
{
    return m_mesh;
}

Material* MeshRenderer::GetMaterial() const
{
    return m_material;
}