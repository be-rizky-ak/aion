#include "AnimationComponent.h"

#include "Aion/Assets/Model.h"
#include "Aion/Math/Matrix4.h"
#include "Aion/Scene/Object3D.h"

namespace Aion
{
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

        if (m_Time > clip.Duration)
        {
            m_Time = fmodf(m_Time, clip.Duration);
        }

        const auto& joints = m_Model->GetJoints();
        if (joints.empty())
        {
            return;
        }

        m_JointMatrices.resize(joints.size(), Matrix4::Identity());

        for (size_t jointIndex = 0; jointIndex < joints.size(); ++jointIndex)
        {
            const auto& joint = joints[jointIndex];

            Matrix4 localTransform = Matrix4::Identity();
            bool found = false;

            for (const auto& channel : clip.Channels)
            {
                if (channel.JointIndex != static_cast<int>(jointIndex))
                {
                    continue;
                }

                AnimationKeyframe prevKeyframe;
                AnimationKeyframe nextKeyframe;

                if (channel.Keyframes.empty())
                {
                    continue;
                }

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

                if (channel.Keyframes.size() == 1)
                {
                    nextKeyframe = channel.Keyframes[0];
                    prevKeyframe = channel.Keyframes[0];
                }

                if (channel.Keyframes.size() > 1)
                {
                    float t = 0.0f;
                    if (nextKeyframe.Time > prevKeyframe.Time)
                    {
                        t = (m_Time - prevKeyframe.Time) / (nextKeyframe.Time - prevKeyframe.Time);
                    }

                    Vector3 translation = prevKeyframe.Translation +
                                          (nextKeyframe.Translation - prevKeyframe.Translation) * t;
                    Quaternion rotation =
                        Quaternion::Slerp(prevKeyframe.Rotation, nextKeyframe.Rotation, t);
                    Vector3 scale =
                        prevKeyframe.Scale + (nextKeyframe.Scale - prevKeyframe.Scale) * t;

                    localTransform = Matrix4::Translate(translation) * Matrix4::Rotate(rotation) *
                                     Matrix4::Scale(scale);
                    found = true;
                }
            }

            if (!found)
            {
                localTransform = Matrix4::Identity();
            }

            Matrix4 global = localTransform;

            if (joint.ParentIndex >= 0 &&
                joint.ParentIndex < static_cast<int>(m_JointMatrices.size()))
            {
                global = m_JointMatrices[joint.ParentIndex] * localTransform;
            }

            m_JointMatrices[jointIndex] = global * joint.InverseBindMatrix;
        }
    }
} // namespace Aion