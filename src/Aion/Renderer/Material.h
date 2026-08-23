#pragma once

#include <cstdint>
#include <memory>

#include <glm/glm.hpp>

#include "RenderState.h"

namespace Aion
{
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
        Material(const std::shared_ptr<Shader>& shader);

        RenderState State{};

        ~Material();

        void Bind();

        const std::shared_ptr<Shader>& GetShader() const;

        void SetNormalTexture(Texture* texture);
        void SetMetallicRoughnessTexture(Texture* texture);
        void SetEmissiveTexture(Texture* texture);
        void SetBaseColorTexture(Texture* texture);
        void SetShader(const std::shared_ptr<Shader>& shader);
        void SetDoubleSided(bool doubleSided);
        void SetTransparent(bool transparent);

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
        std::shared_ptr<Shader> m_shader;
        Texture* m_normalTexture;
        Texture* m_metallicRoughnessTexture;
        Texture* m_emissiveTexture;
        Texture* m_baseColorTexture;
    };
} // namespace Aion