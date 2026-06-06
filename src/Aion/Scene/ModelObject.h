#pragma once

#include "Object3D.h"

class Model;

class ModelObject : public Object3D
{
public:

    ModelObject(Model* model);

    Model* GetModel() const;

private:

    Model* m_model;
};