#include "RenderQueue.h"
#include "Material.h"
#include <algorithm>

namespace Aion
{
    void RenderQueue::Clear()
    {
        m_OpaqueQueue.clear();
        m_TransparentQueue.clear();
    }

    void RenderQueue::Submit(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material,
        const glm::mat4& transform, float distanceToCamera,
        const std::vector<Matrix4>& jointMatrices)
    {
        DrawCommand cmd{std::move(mesh), material, transform, distanceToCamera, jointMatrices};

        if (material && material->State.BlendEnable)
        {
            m_TransparentQueue.push_back(std::move(cmd));
        }
        else
        {
            m_OpaqueQueue.push_back(std::move(cmd));
        }
    }

    void RenderQueue::Sort()
    {
        std::sort(m_OpaqueQueue.begin(), m_OpaqueQueue.end(),
            [](const DrawCommand& a, const DrawCommand& b)
        { return a.DistanceToCamera < b.DistanceToCamera; });

        std::sort(m_TransparentQueue.begin(), m_TransparentQueue.end(),
            [](const DrawCommand& a, const DrawCommand& b)
        { return a.DistanceToCamera > b.DistanceToCamera; });
    }
} // namespace Aion