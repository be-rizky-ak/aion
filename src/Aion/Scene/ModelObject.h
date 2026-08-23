#pragma once

#include "Object3D.h"

namespace Aion
{
    class Model;

    class ModelObject : public Object3D
    {
    public:
        ModelObject(Model* model);

        Model* GetModel() const;

    private:
        Model* m_model;
    };
} // namespace Aion