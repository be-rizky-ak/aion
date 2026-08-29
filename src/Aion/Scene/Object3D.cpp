#include "Object3D.h"

#include <algorithm>

#include "Component.h"
#include "Scene.h"

namespace Aion
{
    Object3D::Object3D() : m_uuid(), m_scene(nullptr), m_parent(nullptr) {}

    void Object3D::SetScene(Scene* scene)
    {
        m_scene = scene;
        for (auto& child : m_children)
        {
            child->SetScene(scene);
        }
    }

    Object3D* Object3D::AddChild(std::unique_ptr<Object3D> child)
    {
        if (!child)
            return nullptr;

        Object3D* rawChild = child.get();
        rawChild->m_parent = this;
        rawChild->SetScene(m_scene);

        m_children.push_back(std::move(child));
        return rawChild;
    }

    std::unique_ptr<Object3D> Object3D::RemoveChild(Object3D* child)
    {
        if (!child || child->m_parent != this)
            return nullptr;

        auto it = std::find_if(m_children.begin(), m_children.end(),
            [child](const std::unique_ptr<Object3D>& ptr) { return ptr.get() == child; });

        if (it != m_children.end())
        {
            std::unique_ptr<Object3D> movedChild = std::move(*it);
            m_children.erase(it);

            movedChild->m_parent = nullptr;
            movedChild->SetScene(nullptr);
            return movedChild;
        }

        return nullptr;
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
        for (auto& component : m_components)
        {
            if (!component->m_started)
            {
                component->OnStart();
                component->SetStarted(true);
            }
        }

        for (auto& child : m_children)
        {
            child->Start();
        }
    }

    void Object3D::Update(float deltaTime)
    {
        for (auto& component : m_components)
        {
            if (component->IsEnabled())
            {
                component->OnUpdate(deltaTime);
            }
        }

        for (auto& child : m_children)
        {
            child->Update(deltaTime);
        }
    }

    void Object3D::OnEvent(Event& event)
    {
        for (auto& component : m_components)
        {
            component->OnEvent(event);
        }

        for (auto& child : m_children)
        {
            child->OnEvent(event);
        }
    }
} // namespace Aion