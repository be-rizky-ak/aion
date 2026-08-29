#pragma once

#include <memory>
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
        ~Scene() = default;

        void Add(std::shared_ptr<Object3D> object);
        void RemoveRoot(const std::shared_ptr<Object3D>& object);
        void AddRoot(std::shared_ptr<Object3D> object);

        std::shared_ptr<Object3D> GetObjectByUUID(UUID uuid);

        void SetActiveCamera(CameraComponent* camera);
        CameraComponent* GetActiveCamera() const;

        void Start();
        void Update(float deltaTime);

        void OnEvent(Event& event);

        const std::vector<std::shared_ptr<Object3D>>& GetObjects() const;

    private:
        std::vector<std::shared_ptr<Object3D>> m_objects;
        std::unordered_map<UUID, std::shared_ptr<Object3D>> m_objectMap;
        CameraComponent* m_activeCamera;

        bool m_started;
    };
} // namespace Aion