#pragma once

class Object3D;
class Transform;
class Event;

class Component
{
  public:
    Component();
    virtual ~Component();

    virtual void OnStart()
    {
    }
    virtual void OnCreate()
    {
    }
    virtual void OnUpdate(float deltaTime)
    {
    }
    virtual void OnDestroy() {};
    virtual void OnEvent(Event& event)
    {
    }

    Object3D* GetOwner() const;
    Transform& GetTransform() const;

    void SetOwner(Object3D* owner);

    bool IsEnabled() const;
    bool IsStarted() const;
    void SetEnabled(bool enabled);
    void SetStarted(bool started);

  private:
    friend class Object3D;

    Object3D* m_owner;

    bool m_enabled;
    bool m_started;
};