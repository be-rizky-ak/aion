#include "MaterialInstance.h"

#include <type_traits>
#include <variant>

#include "Shader.h"
#include "Texture.h"
#include "TextureLibrary.h"

namespace Aion
{
    MaterialInstance::MaterialInstance(const std::shared_ptr<Material>& parentMaterial)
        : m_parent(parentMaterial)
    {
    }

    void MaterialInstance::SetBaseColor(const Vector4& color)
    {
        BaseColor = color;
        m_HasBaseColorOverride = true;
    }

    void MaterialInstance::SetMetallic(float metallic)
    {
        MetallicFactor = metallic;
        m_HasMetallicOverride = true;
    }

    void MaterialInstance::SetRoughness(float roughness)
    {
        RoughnessFactor = roughness;
        m_HasRoughnessOverride = true;
    }

    void MaterialInstance::SetEmissive(const Vector3& emissive)
    {
        EmissiveFactor = emissive;
        m_HasEmissiveOverride = true;
    }

    void MaterialInstance::Bind()
    {
        std::shared_ptr<Shader> activeShader =
            m_shader ? m_shader : (m_parent ? m_parent->GetShader() : nullptr);
        if (!activeShader)
        {
            return;
        }

        activeShader->Use();

        Vector4 resolvedBaseColor =
            m_HasBaseColorOverride ? BaseColor : (m_parent ? m_parent->BaseColor : Vector4(1.0f));
        float resolvedMetallic =
            m_HasMetallicOverride ? MetallicFactor : (m_parent ? m_parent->MetallicFactor : 1.0f);
        float resolvedRoughness = m_HasRoughnessOverride
                                      ? RoughnessFactor
                                      : (m_parent ? m_parent->RoughnessFactor : 1.0f);
        Vector3 resolvedEmissive = m_HasEmissiveOverride
                                       ? EmissiveFactor
                                       : (m_parent ? m_parent->EmissiveFactor : Vector3(0.0f));

        activeShader->SetVec4("u_BaseColor", resolvedBaseColor);
        activeShader->SetFloat("u_MetallicFactor", resolvedMetallic);
        activeShader->SetFloat("u_RoughnessFactor", resolvedRoughness);
        activeShader->SetVec3("u_EmissiveFactor", resolvedEmissive);

        if (m_parent)
        {
            m_parent->BindUniformsAndTextures(activeShader);
        }

        BindUniformsAndTextures(activeShader);
    }
} // namespace Aion