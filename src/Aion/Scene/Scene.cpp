#include "Scene.h"

#include <algorithm>

#include "../Core/Event.h"
#include "CameraComponent.h"
#include "Object3D.h"

namespace Aion
{
    Scene::Scene() : m_activeCamera(nullptr), m_started(false) {}

    void Scene::Add(std::shared_ptr<Object3D> object)
    {
        if (!object)
            return;

        object->SetScene(this);

        m_objectMap[object->GetUUID()] = object;

        if (!object->GetParent())
        {
            m_objects.push_back(object);
        }

        if (m_started)
        {
            object->Start();
        }
    }

    void Scene::AddRoot(std::shared_ptr<Object3D> object)
    {
        if (object)
        {
            m_objects.push_back(object);
        }
    }

    void Scene::RemoveRoot(const std::shared_ptr<Object3D>& object)
    {
        auto it = std::find(m_objects.begin(), m_objects.end(), object);
        if (it != m_objects.end())
        {
            m_objects.erase(it);
        }
    }

    std::shared_ptr<Object3D> Scene::GetObjectByUUID(UUID uuid)
    {
        auto it = m_objectMap.find(uuid);
        if (it != m_objectMap.end())
        {
            return it->second;
        }
        return nullptr;
    }

    const std::vector<std::shared_ptr<Object3D>>& Scene::GetObjects() const
    {
        return m_objects;
    }

    void Scene::SetActiveCamera(CameraComponent* camera)
    {
        m_activeCamera = camera;
    }

    CameraComponent* Scene::GetActiveCamera() const
    {
        return m_activeCamera;
    }

    void Scene::Start()
    {
        for (auto& object : m_objects)
        {
            if (object)
                object->Start();
        }

        m_started = true;
    }

    void Scene::Update(float deltaTime)
    {
        for (auto& object : m_objects)
        {
            if (object)
                object->Update(deltaTime);
        }
    }

    void Scene::OnEvent(Event& event)
    {
        for (auto& object : m_objects)
        {
            if (object)
                object->OnEvent(event);
        }
    }
} // namespace Aion