#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace Aion
{
    class Mesh;
    class Material;

    struct DrawCommand
    {
        std::shared_ptr<Mesh> MeshPtr;
        std::shared_ptr<Material> MaterialPtr;
        glm::mat4 Transform;
        float DistanceToCamera;
    };

    class RenderQueue
    {
    public:
        void Clear();
        void Submit(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material,
            const glm::mat4& transform, float distanceToCamera);
        void Sort();

        const std::vector<DrawCommand>& GetOpaqueQueue() const { return m_OpaqueQueue; }
        const std::vector<DrawCommand>& GetTransparentQueue() const { return m_TransparentQueue; }

    private:
        std::vector<DrawCommand> m_OpaqueQueue;
        std::vector<DrawCommand> m_TransparentQueue;
    };
} // namespace Aion