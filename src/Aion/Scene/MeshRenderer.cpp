#include "MeshRenderer.h"

namespace Aion
{
    MeshRenderer::MeshRenderer(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material)
        : m_mesh(std::move(mesh)), m_material(std::move(material))
    {
    }

    void MeshRenderer::SetMesh(std::shared_ptr<Mesh> mesh)
    {
        m_mesh = std::move(mesh);
    }

    std::shared_ptr<Mesh> MeshRenderer::GetMesh() const
    {
        return m_mesh;
    }

    void MeshRenderer::SetMaterial(std::shared_ptr<Material> material)
    {
        m_material = std::move(material);
    }

    std::shared_ptr<Material> MeshRenderer::GetMaterial() const
    {
        return m_material;
    }
} // namespace Aion