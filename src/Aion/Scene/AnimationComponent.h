#pragma once

#include <memory>
#include <vector>

#include "Aion/Assets/Model.h"
#include "Aion/Math/Matrix4.h"

#include "Component.h"

namespace Aion
{
    class AnimationComponent : public Component
    {
    public:
        AnimationComponent(std::shared_ptr<Model> model);
        void OnUpdate(float deltaTime) override;
        void PlayClip(size_t clipIndex);
        const std::vector<Matrix4>& GetJointMatrices() const;

    private:
        std::shared_ptr<Model> m_Model;
        size_t m_ActiveClip = 0;
        float m_Time = 0.0f;
        std::vector<Matrix4> m_JointMatrices;
    };
} // namespace Aion