#pragma once

#include "Component.h"

namespace Aion
{
    class Model;

    class ModelComponent : public Component
    {
    public:
        ModelComponent(Model* model) : m_model(model) {}

        ~ModelComponent() { delete m_model; }

    private:
        Model* m_model;
    };
} // namespace Aion