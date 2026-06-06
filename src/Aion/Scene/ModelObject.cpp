#include "ModelObject.h"

ModelObject::ModelObject(Model* model)
{
    m_model = model;
}

Model* ModelObject::GetModel() const
{
    return m_model;
}