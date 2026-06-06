#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(
    Mesh* mesh,
    Material* material
)
    :
    m_Mesh(mesh),
    m_Material(material)
{
}

Mesh* MeshRenderer::GetMesh() const
{
    return m_Mesh;
}

Material* MeshRenderer::GetMaterial() const
{
    return m_Material;
}