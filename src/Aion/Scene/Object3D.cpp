#include "Object3D.h"

#include <algorithm>

#include "Component.h"
#include "Scene.h"

namespace Aion
{
    Object3D::Object3D() : m_uuid(), m_scene(nullptr), m_parent(nullptr) {}

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

    void Object3D::SetScene(Scene* scene)
    {
        m_scene = scene;
        for (Object3D* child : m_children)
        {
            child->SetScene(scene);
        }
    }

    void Object3D::AddChild(Object3D* child)
    {
        if (!child)
            return;
        child->SetParent(this);
    }

    void Object3D::RemoveChild(Object3D* child)
    {
        if (!child || child->GetParent() != this)
            return;
        child->SetParent(nullptr);
    }

    void Object3D::SetParent(Object3D* parent)
    {
        if (m_parent == parent)
        {
            return;
        }

        if (m_parent)
        {
            auto& siblings = m_parent->m_children;
            siblings.erase(std::remove(siblings.begin(), siblings.end(), this), siblings.end());
        }
        else if (m_scene)
        {
            m_scene->RemoveRoot(this);
        }

        m_parent = parent;

        if (m_parent)
        {
            m_parent->m_children.push_back(this);
            SetScene(m_parent->GetScene());
        }
        else if (m_scene)
        {
            m_scene->AddRoot(this);
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

    Matrix4 Object3D::GetWorldMatrix() const
    {
        Matrix4 local = Transform.GetMatrix();

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

        for (Object3D* child : m_children)
        {
            child->Start();
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
        for (Component* component : m_components)
        {
            component->OnEvent(event);
        }

        for (Object3D* child : m_children)
        {
            child->OnEvent(event);
        }
    }
} // namespace Aion