#pragma once

#include <vector>

class Object3D;

class Scene
{
public:

    void Add(Object3D* object);

    const std::vector<Object3D*>& GetObjects() const;

private:

    std::vector<Object3D*> m_objects;
};