#include "ModelObject.h"

namespace Aion
{
    ModelObject::ModelObject(Model* model)
    {
        m_model = model;
    }

    Model* ModelObject::GetModel() const
    {
        return m_model;
    }
} // namespace Aion