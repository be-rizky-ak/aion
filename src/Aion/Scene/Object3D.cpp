#include "Object3D.h"

#include "Component.h"
#include "MeshRenderer.h"

Object3D::Object3D() : m_parent(nullptr)
{
}

Object3D::~Object3D()
{
    for (Component* component : m_components)
    {
        component->OnDestroy();
        delete component;
    }

    for (Object3D* child : m_children)
    {
        delete child;
    }
}

void Object3D::AddChild(Object3D* child)
{
    if (!child)
    {
        return;
    }

    child->m_parent = this;

    m_children.push_back(child);
}

void Object3D::RemoveChild(Object3D* child)
{
    auto it = std::find(m_children.begin(), m_children.end(), child);

    if (it != m_children.end())
    {
        (*it)->m_parent = nullptr;

        m_children.erase(it);
    }
}

void Object3D::SetParent(Object3D* parent)
{
    if (m_parent)
    {
        auto& siblings = m_parent->m_children;

        siblings.erase(std::remove(siblings.begin(), siblings.end(), this), siblings.end());
    }

    m_parent = parent;

    if (m_parent)
    {
        m_parent->m_children.push_back(this);
    }
}

Object3D* Object3D::GetParent() const
{
    return m_parent;
}

const std::vector<Object3D*>& Object3D::GetChildren() const
{
    return m_children;
}

glm::mat4 Object3D::GetWorldMatrix() const
{
    glm::mat4 local = Transform.GetMatrix();

    if (!m_parent)
    {
        return local;
    }

    return m_parent->GetWorldMatrix() * local;
}

void Object3D::Start()
{
    for (Component* component : m_components)
    {
        if (!component->m_started)
        {
            component->OnStart();
            component->SetStarted(true);
        }
    }
}

void Object3D::Update(float deltaTime)
{
    for (Component* component : m_components)
    {
        if (!component->IsEnabled())
        {
            continue;
        }

        component->OnUpdate(deltaTime);
    }

    for (Object3D* child : m_children)
    {
        child->Update(deltaTime);
    }
}

void Object3D::OnEvent(Event& event)
{
    for (Component* component :
         m_components)
    {
        component->OnEvent(event);
    }

    for (Object3D* child :
         m_children)
    {
        child->OnEvent(event);
    }
}