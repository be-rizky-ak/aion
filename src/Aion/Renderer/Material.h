#pragma once

#include <glm/glm.hpp>

class Shader;
class Texture;

enum class MaterialTextureSlot
{
    Albedo,
    Normal,
    MetallicRoughness,
    Emissive
};

enum class AlphaMode
{
    Opaque,
    Mask,
    Blend
};

class Material
{
  public:
    Material();
    Material(Shader* shader);

    ~Material();

    void Bind();

    Shader* GetShader() const;

    void SetNormalTexture(Texture* texture);
    void SetMetallicRoughnessTexture(Texture* texture);
    void SetEmissiveTexture(Texture* texture);
    void SetBaseColorTexture(Texture* texture);
    void SetShader(Shader* shader);

    Texture* GetNormalTexture() const;
    Texture* GetMetallicRoughnessTexture() const;
    Texture* GetEmissiveTexture() const;
    Texture* GetBaseColorTexture() const;

  public:
    glm::vec4 BaseColor;

    float MetallicFactor;
    float RoughnessFactor;

    glm::vec3 EmissiveFactor;

    AlphaMode AlphaModeType;
    float AlphaCutoff;
    bool DoubleSided;

  private:
    Shader* m_shader;
    Texture* m_normalTexture;
    Texture* m_metallicRoughnessTexture;
    Texture* m_emissiveTexture;
    Texture* m_baseColorTexture;
};