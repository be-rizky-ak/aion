#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <variant>

#include "Aion/Math/Matrix4.h"
#include "Aion/Math/Vector2.h"
#include "Aion/Math/Vector3.h"
#include "Aion/Math/Vector4.h"

#include "RenderState.h"

namespace Aion
{
    class Shader;
    class Texture;

    enum class MaterialTextureSlot : uint32_t
    {
        Albedo = 0,
        Normal = 1,
        MetallicRoughness = 2,
        Emissive = 3,
        AO = 4,
        CustomStart = 5
    };

    enum class AlphaMode
    {
        Opaque,
        Mask,
        Blend
    };

    using UniformValue = std::variant<int, float, Vector2, Vector3, Vector4, Matrix4>;

    class Material
    {
        friend class MaterialInstance;

    public:
        Material();
        explicit Material(const std::shared_ptr<Shader>& shader);
        virtual ~Material() = default;

        virtual void Bind();

        const std::shared_ptr<Shader>& GetShader() const { return m_shader; }
        void SetShader(const std::shared_ptr<Shader>& shader);

        // Uniform Setters
        void SetInt(const std::string& name, int value);
        void SetFloat(const std::string& name, float value);
        void SetVector2(const std::string& name, const Vector2& value);
        void SetVector3(const std::string& name, const Vector3& value);
        void SetVector4(const std::string& name, const Vector4& value);
        void SetMatrix4(const std::string& name, const Matrix4& value);

        // Texture Slot Setters
        void SetTexture(uint32_t slot, const std::shared_ptr<Texture>& texture);
        void SetTexture(
            const std::string& uniformName, uint32_t slot, const std::shared_ptr<Texture>& texture);
        std::shared_ptr<Texture> GetTexture(uint32_t slot) const;

        void SetBaseColorTexture(const std::shared_ptr<Texture>& texture);
        void SetNormalTexture(const std::shared_ptr<Texture>& texture);
        void SetMetallicRoughnessTexture(const std::shared_ptr<Texture>& texture);
        void SetEmissiveTexture(const std::shared_ptr<Texture>& texture);

        void SetDoubleSided(bool doubleSided);
        void SetTransparent(bool transparent);

    public:
        RenderState State{};
        Vector4 BaseColor{1.0f, 1.0f, 1.0f, 1.0f};
        float MetallicFactor = 1.0f;
        float RoughnessFactor = 1.0f;
        Vector3 EmissiveFactor{0.0f, 0.0f, 0.0f};

        AlphaMode AlphaModeType = AlphaMode::Opaque;
        float AlphaCutoff = 0.5f;
        bool DoubleSided = false;

    protected:
        struct TextureBinding
        {
            std::string UniformName;
            uint32_t Slot = 0;
            std::shared_ptr<Texture> TexturePtr;
        };

        void BindUniformsAndTextures(const std::shared_ptr<Shader>& shader) const;

        std::shared_ptr<Shader> m_shader;
        std::unordered_map<std::string, UniformValue> m_Uniforms;
        std::unordered_map<uint32_t, TextureBinding> m_Textures;
    };
} // namespace Aion