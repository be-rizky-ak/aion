#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Aion/Core/UUID.h"
#include "AnimationComponent.h"
#include "CameraComponent.h"
#include "Transform.h"

namespace Aion
{
    class Event;
    class Component;
    class Scene;

    class Object3D
    {
    public:
        Object3D();
        ~Object3D() = default;

        virtual void OnEvent(Event& event);

        Transform Transform;

        UUID GetUUID() const { return m_uuid; }

        Object3D* AddChild(std::unique_ptr<Object3D> child);
        std::unique_ptr<Object3D> RemoveChild(Object3D* child);

        void Start();
        void Update(float deltaTime);

        void SetScene(Scene* scene);
        Scene* GetScene() const { return m_scene; }

        Object3D* GetParent() const { return m_parent; }
        const std::vector<std::unique_ptr<Object3D>>& GetChildren() const { return m_children; }
        Matrix4 GetWorldMatrix() const;

        template <typename T, typename... Args> T* AddComponent(Args&&... args)
        {
            static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");

            auto component = std::make_unique<T>(std::forward<Args>(args)...);
            T* rawPtr = component.get();

            component->m_owner = this;
            m_components.push_back(std::move(component));
            rawPtr->OnCreate();

            return rawPtr;
        }

        template <typename T> T* GetComponent() const
        {
            for (const auto& component : m_components)
            {
                T* result = dynamic_cast<T*>(component.get());
                if (result)
                {
                    return result;
                }
            }

            return nullptr;
        }

    private:
        UUID m_uuid;
        Scene* m_scene = nullptr;
        Object3D* m_parent = nullptr; // Non-owning raw pointer
        std::vector<std::unique_ptr<Object3D>> m_children;
        std::vector<std::unique_ptr<Component>> m_components;
    };
} // namespace Aion