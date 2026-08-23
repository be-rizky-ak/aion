#pragma once

#include <unordered_map>
#include <vector>

#include "../Core/UUID.h"

namespace Aion
{
    class Event;
    class CameraComponent;
    class Object3D;

    class Scene
    {
    public:
        Scene();
        ~Scene();

        void Add(Object3D* object);
        void RemoveRoot(Object3D* object);
        void AddRoot(Object3D* object);

        Object3D* GetObjectByUUID(UUID uuid);

        void SetActiveCamera(CameraComponent* camera);
        CameraComponent* GetActiveCamera() const;

        void Start();
        void Update(float deltaTime);

        void OnEvent(Event& event);

        const std::vector<Object3D*>& GetObjects() const;

    private:
        std::vector<Object3D*> m_objects;
        std::unordered_map<UUID, Object3D*> m_objectMap;
        CameraComponent* m_activeCamera;

        bool m_started;
    };
} // namespace Aion