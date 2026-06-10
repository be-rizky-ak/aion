#include "Component.h"

#include "Object3D.h"

Component::Component() : m_owner(nullptr), m_enabled(true), m_started(false)
{
}

Component::~Component()
{
}

Object3D* Component::GetOwner() const
{
    return m_owner;
}

void Component::SetOwner(Object3D* owner)
{
    m_owner = owner;
}

Transform& Component::GetTransform() const
{
    return m_owner->Transform;
}

bool Component::IsEnabled() const
{
    return m_enabled;
}

void Component::SetEnabled(bool enabled)
{
    m_enabled = enabled;
}

bool Component::IsStarted() const
{
    return m_started;
}

void Component::SetStarted(bool started)
{
    m_started = started;
}