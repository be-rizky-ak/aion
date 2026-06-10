#include "Scene.h"

#include "../Core/Event.h"
#include "Camera.h"
#include "Object3D.h"

Scene::Scene() : m_activeCamera(nullptr), m_started(false)
{
}

Scene::~Scene()
{
    for (Object3D* object : m_objects)
    {
        delete object;
    }
}

void Scene::Add(Object3D* object)
{
    if (object->GetParent())
    {
        return;
    }

    m_objects.push_back(object);

    if (m_started)
    {
        object->Start();
    }
}

const std::vector<Object3D*>& Scene::GetObjects() const
{
    return m_objects;
}

void Scene::SetActiveCamera(Camera* camera)
{
    m_activeCamera = camera;
}

Camera* Scene::GetActiveCamera() const
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