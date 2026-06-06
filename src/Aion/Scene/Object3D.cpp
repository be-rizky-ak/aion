#include "Object3D.h"

#include "MeshRenderer.h"

Object3D::Object3D()
{
    m_meshRenderer = nullptr;
}

Object3D::~Object3D()
{
}

void Object3D::SetMeshRenderer(
    MeshRenderer* renderer)
{
    m_meshRenderer = renderer;
}

MeshRenderer* Object3D::GetMeshRenderer() const
{
    return m_meshRenderer;
}