#include "Scene.h"

#include "Object3D.h"

void Scene::Add(Object3D* object)
{
    m_objects.push_back(object);
}

const std::vector<Object3D*>& Scene::GetObjects() const
{
    return m_objects;
}