#include "AnimationComponent.h"

#include <functional>

#include "Aion/Assets/Model.h"
#include "Aion/Math/Matrix4.h"
#include "Aion/Scene/MeshRenderer.h"
#include "Aion/Scene/Object3D.h"

namespace Aion
{
    static void UpdateMeshRenderers(Object3D* object, const std::vector<Matrix4>& jointMatrices)
    {
        if (!object)
        {
            return;
        }

        if (auto* mr = object->GetComponent<MeshRenderer>())
        {
            mr->SetJointMatrices(jointMatrices);
        }

        for (const auto& child : object->GetChildren())
        {
            UpdateMeshRenderers(child.get(), jointMatrices);
        }
    }

    AnimationComponent::AnimationComponent(std::shared_ptr<Model> model) : m_Model(model)
    {
        if (m_Model && !m_Model->GetAnimations().empty())
        {
            m_ActiveClip = 0;
            m_JointMatrices.resize(m_Model->GetJoints().size(), Matrix4::Identity());
        }
    }

    void AnimationComponent::PlayClip(size_t clipIndex)
    {
        if (!m_Model)
        {
            return;
        }

        const auto& clips = m_Model->GetAnimations();
        if (clipIndex >= clips.size())
        {
            return;
        }

        m_ActiveClip = clipIndex;
        m_Time = 0.0f;
    }

    const std::vector<Matrix4>& AnimationComponent::GetJointMatrices() const
    {
        return m_JointMatrices;
    }

    void AnimationComponent::OnUpdate(float deltaTime)
    {
        if (!m_Model)
        {
            return;
        }

        const auto& clips = m_Model->GetAnimations();
        if (clips.empty())
        {
            return;
        }

        const auto& clip = clips[m_ActiveClip];
        m_Time += deltaTime;

        if (clip.Duration > 0.0f && m_Time > clip.Duration)
        {
            m_Time = fmodf(m_Time, clip.Duration);
        }

        const auto& joints = m_Model->GetJoints();
        if (joints.empty())
        {
            return;
        }

        m_JointMatrices.resize(joints.size(), Matrix4::Identity());

        std::vector<Matrix4> localTransforms(joints.size(), Matrix4::Identity());

        for (size_t jointIndex = 0; jointIndex < joints.size(); ++jointIndex)
        {
            Vector3 translation(0.0f);
            Quaternion rotation = Quaternion::Identity();
            Vector3 scale(1.0f);

            for (const auto& channel : clip.Channels)
            {
                if (channel.JointIndex != static_cast<int>(jointIndex))
                {
                    continue;
                }

                if (channel.Keyframes.empty())
                {
                    continue;
                }

                AnimationKeyframe prevKeyframe = channel.Keyframes[0];
                AnimationKeyframe nextKeyframe = channel.Keyframes[0];

                for (size_t k = 0; k < channel.Keyframes.size(); ++k)
                {
                    const auto& keyframe = channel.Keyframes[k];
                    if (keyframe.Time <= m_Time)
                    {
                        prevKeyframe = keyframe;
                    }
                    if (keyframe.Time >= m_Time)
                    {
                        nextKeyframe = keyframe;
                        break;
                    }
                }

                float t = 0.0f;
                if (nextKeyframe.Time > prevKeyframe.Time)
                {
                    t = (m_Time - prevKeyframe.Time) / (nextKeyframe.Time - prevKeyframe.Time);
                }

                if (channel.Path == "translation")
                {
                    translation = prevKeyframe.Translation +
                                  (nextKeyframe.Translation - prevKeyframe.Translation) * t;
                }
                else if (channel.Path == "rotation")
                {
                    rotation = Quaternion::Slerp(prevKeyframe.Rotation, nextKeyframe.Rotation, t);
                }
                else if (channel.Path == "scale")
                {
                    scale = prevKeyframe.Scale + (nextKeyframe.Scale - prevKeyframe.Scale) * t;
                }
            }

            localTransforms[jointIndex] = Matrix4::Translate(translation) *
                                           Matrix4::Rotate(rotation) *
                                           Matrix4::Scale(scale);
        }

        std::vector<Matrix4> globalTransforms(joints.size(), Matrix4::Identity());
        std::vector<bool> computed(joints.size(), false);

        std::function<Matrix4(size_t)> getGlobalTransform = [&](size_t idx) -> Matrix4 {
            if (computed[idx])
            {
                return globalTransforms[idx];
            }

            Matrix4 parentGlobal = Matrix4::Identity();
            if (joints[idx].ParentIndex >= 0 &&
                joints[idx].ParentIndex < static_cast<int>(joints.size()))
            {
                parentGlobal = getGlobalTransform(joints[idx].ParentIndex);
            }

            globalTransforms[idx] = parentGlobal * localTransforms[idx];
            computed[idx] = true;
            return globalTransforms[idx];
        };

        for (size_t i = 0; i < joints.size(); ++i)
        {
            getGlobalTransform(i);
            m_JointMatrices[i] = globalTransforms[i] * joints[i].InverseBindMatrix;
        }

        if (GetOwner())
        {
            UpdateMeshRenderers(GetOwner(), m_JointMatrices);
        }
    }
} // namespace Aion