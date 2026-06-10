#pragma once

#include <string>
#include <vector>

#include "Transform.h"

class Event;
class Component;

class Object3D
{
  public:
    Object3D();
    virtual ~Object3D();

    virtual void OnEvent(Event& event);

    Transform Transform;

    void AddChild(Object3D* child);
    void RemoveChild(Object3D* child);
    void SetParent(Object3D* parent);

    void Start();
    void Update(float deltaTime);

    Object3D* GetParent() const;
    const std::vector<Object3D*>& GetChildren() const;
    glm::mat4 GetWorldMatrix() const;

    template <typename T, typename... Args> T* AddComponent(Args&&... args)
    {
        T* component = new T(std::forward<Args>(args)...);

        component->m_owner = this;

        m_components.push_back(component);

        component->OnCreate();

        return component;
    }

    template <typename T> T* GetComponent() const
    {
        for (Component* component : m_components)
        {
            T* result = dynamic_cast<T*>(component);

            if (result)
            {
                return result;
            }
        }

        return nullptr;
    }

  private:
    Object3D* m_parent;
    std::vector<Object3D*> m_children;
    std::vector<Component*> m_components;
};