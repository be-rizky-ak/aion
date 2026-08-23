#include "Material.h"

#include <glad/glad.h>

#include "Shader.h"
#include "ShaderLibrary.h"
#include "Texture.h"

namespace Aion
{
    Material::Material()
        : m_shader(ShaderLibrary::GetDefault()), m_normalTexture(nullptr),
          m_metallicRoughnessTexture(nullptr), m_emissiveTexture(nullptr),
          m_baseColorTexture(nullptr), BaseColor(glm::vec4(1.0f)), MetallicFactor(1.0f),
          RoughnessFactor(1.0f), EmissiveFactor(glm::vec3(0.0f)), AlphaModeType(AlphaMode::Blend),
          AlphaCutoff(0.5f), DoubleSided(false)
    {
    }

    Material::Material(const std::shared_ptr<Shader>& shader)
        : m_shader(shader ? shader : ShaderLibrary::GetDefault()), m_normalTexture(nullptr),
          m_metallicRoughnessTexture(nullptr), m_emissiveTexture(nullptr),
          m_baseColorTexture(nullptr), BaseColor(glm::vec4(1.0f)), MetallicFactor(1.0f),
          RoughnessFactor(1.0f), EmissiveFactor(glm::vec3(0.0f)), AlphaModeType(AlphaMode::Blend),
          AlphaCutoff(0.5f), DoubleSided(false)
    {
    }

    Material::~Material() {}

    void Material::Bind()
    {
        if (!m_shader)
            return;

        m_shader->SetVec4("u_BaseColor", BaseColor);
        m_shader->SetFloat("u_MetallicFactor", MetallicFactor);
        m_shader->SetFloat("u_RoughnessFactor", RoughnessFactor);
        m_shader->SetVec3("u_EmissiveFactor", EmissiveFactor);

        if (m_baseColorTexture)
        {
            m_shader->SetInt("u_BaseColorTexture", 0);
            m_baseColorTexture->Bind(0);
        }

        if (m_normalTexture)
        {
            m_shader->SetInt("u_NormalTexture", 1);
            m_normalTexture->Bind(1);
        }

        if (m_metallicRoughnessTexture)
        {
            m_shader->SetInt("u_MetallicRoughnessTexture", 2);
            m_metallicRoughnessTexture->Bind(2);
        }

        if (m_emissiveTexture)
        {
            m_shader->SetInt("u_EmissiveTexture", 3);
            m_emissiveTexture->Bind(3);
        }
    }

    const std::shared_ptr<Shader>& Material::GetShader() const
    {
        return m_shader;
    }

    void Material::SetNormalTexture(Texture* texture)
    {
        m_normalTexture = texture;
    }

    void Material::SetMetallicRoughnessTexture(Texture* texture)
    {
        m_metallicRoughnessTexture = texture;
    }

    void Material::SetEmissiveTexture(Texture* texture)
    {
        m_emissiveTexture = texture;
    }

    void Material::SetBaseColorTexture(Texture* texture)
    {
        m_baseColorTexture = texture;
    }

    void Material::SetDoubleSided(bool doubleSided)
    {
        DoubleSided = doubleSided;
        State.CullingMode = doubleSided ? CullMode::None : CullMode::Back;
    }

    void Material::SetTransparent(bool transparent)
    {
        State.BlendEnable = transparent;
        State.DepthWrite = !transparent;
    }

    Texture* Material::GetNormalTexture() const
    {
        return m_normalTexture;
    }

    Texture* Material::GetMetallicRoughnessTexture() const
    {
        return m_metallicRoughnessTexture;
    }

    Texture* Material::GetEmissiveTexture() const
    {
        return m_emissiveTexture;
    }

    Texture* Material::GetBaseColorTexture() const
    {
        return m_baseColorTexture;
    }

    void Material::SetShader(const std::shared_ptr<Shader>& shader)
    {
        m_shader = shader ? shader : ShaderLibrary::GetDefault();
    }
} // namespace Aion