#pragma once

#include <memory>

#include "Component.h"

namespace Aion
{
    class Model;

    class ModelComponent : public Component
    {
    public:
        ModelComponent(std::shared_ptr<Model> model) : m_Model(model) {}
        std::shared_ptr<Model> GetModel() const { return m_Model; }
    private:
        std::shared_ptr<Model> m_Model;
    };
} // namespace Aion