#include "Scene.h"

#include <algorithm>

#include "../Core/Event.h"
#include "CameraComponent.h"
#include "Object3D.h"
#include "Scene.h"

namespace Aion
{
    Scene::Scene() : m_activeCamera(nullptr), m_started(false) {}

    Scene::~Scene()
    {
        for (Object3D* object : m_objects)
        {
            delete object;
        }
    }

    void Scene::Add(Object3D* object)
    {
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

    void Scene::AddRoot(Object3D* object)
    {
        m_objects.push_back(object);
    }

    void Scene::RemoveRoot(Object3D* object)
    {
        auto it = std::find(m_objects.begin(), m_objects.end(), object);
        if (it != m_objects.end())
        {
            m_objects.erase(it);
        }
    }

    Object3D* Scene::GetObjectByUUID(UUID uuid)
    {
        if (m_objectMap.find(uuid) != m_objectMap.end())
        {
            return m_objectMap[uuid];
        }
        return nullptr;
    }

    const std::vector<Object3D*>& Scene::GetObjects() const
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
        for (Object3D* object : m_objects)
        {
            object->Start();
        }

        m_started = true;
    }

    void Scene::Update(float deltaTime)
    {
        for (Object3D* object : m_objects)
        {
            object->Update(deltaTime);
        }
    }

    void Scene::OnEvent(Event& event)
    {
        for (Object3D* object : m_objects)
        {
            object->OnEvent(event);
        }
    }
} // namespace Aion