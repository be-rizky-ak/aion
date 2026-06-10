#pragma once

#include <vector>

class Event;
class Camera;
class Object3D;

class Scene
{
  public:
    Scene();
    ~Scene();

    void Add(Object3D* object);
    void SetActiveCamera(Camera* camera);

    void Start();
    void Update(float deltaTime);

    void OnEvent(Event& event);

    const std::vector<Object3D*>& GetObjects() const;
    Camera* GetActiveCamera() const;

  private:
    std::vector<Object3D*> m_objects;
    Camera* m_activeCamera;

    bool m_started;
};