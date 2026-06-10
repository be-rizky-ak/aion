#pragma once

#include "Component.h"

class Model;

class ModelComponent : public Component
{
  public:
    ModelComponent(Model* model) : m_model(model)
    {
    }

    ~ModelComponent()
    {
        delete m_model;
    }

  private:
    Model* m_model;
};