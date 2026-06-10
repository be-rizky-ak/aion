#include "Material.h"

#include <glad/glad.h>

#include "Shader.h"
#include "Texture.h"

Material::Material()
    : m_shader(nullptr), m_normalTexture(nullptr), m_metallicRoughnessTexture(nullptr), m_emissiveTexture(nullptr),
      m_baseColorTexture(nullptr), BaseColor(glm::vec4(1.0f)), MetallicFactor(1.0f), RoughnessFactor(1.0f),
      EmissiveFactor(glm::vec3(0.0f)), AlphaModeType(AlphaMode::Blend), AlphaCutoff(0.5f), DoubleSided(false)
{
}

Material::Material(Shader* shader)
    : m_shader(shader), m_normalTexture(nullptr), m_metallicRoughnessTexture(nullptr), m_emissiveTexture(nullptr),
      m_baseColorTexture(nullptr), BaseColor(glm::vec4(1.0f)), MetallicFactor(1.0f), RoughnessFactor(1.0f),
      EmissiveFactor(glm::vec3(0.0f)), AlphaModeType(AlphaMode::Blend), AlphaCutoff(0.5f), DoubleSided(false)
{
}

Material::~Material()
{
}

void Material::Bind()
{
    if (m_baseColorTexture)
    {
        m_baseColorTexture->Bind(0);
    }

    if (m_normalTexture)
    {
        m_normalTexture->Bind(1);
    }

    if (m_metallicRoughnessTexture)
    {
        m_metallicRoughnessTexture->Bind(2);
    }

    if (m_emissiveTexture)
    {
        m_emissiveTexture->Bind(3);
    }
}

Shader* Material::GetShader() const
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

void Material::SetShader(Shader* shader)
{
    m_shader = shader;
}