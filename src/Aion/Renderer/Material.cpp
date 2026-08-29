#include "Material.h"

#include "Shader.h"
#include "ShaderLibrary.h"
#include "Texture.h"
#include "TextureLibrary.h"

namespace Aion
{
    Material::Material() : m_shader(ShaderLibrary::GetDefault()) {}

    Material::Material(const std::shared_ptr<Shader>& shader)
        : m_shader(shader ? shader : ShaderLibrary::GetDefault())
    {
    }

    void Material::SetShader(const std::shared_ptr<Shader>& shader)
    {
        m_shader = shader ? shader : ShaderLibrary::GetDefault();
    }

    void Material::SetInt(const std::string& name, int value)
    {
        m_Uniforms[name] = value;
    }
    void Material::SetFloat(const std::string& name, float value)
    {
        m_Uniforms[name] = value;
    }
    void Material::SetVector2(const std::string& name, const Vector2& value)
    {
        m_Uniforms[name] = value;
    }
    void Material::SetVector3(const std::string& name, const Vector3& value)
    {
        m_Uniforms[name] = value;
    }
    void Material::SetVector4(const std::string& name, const Vector4& value)
    {
        m_Uniforms[name] = value;
    }
    void Material::SetMatrix4(const std::string& name, const Matrix4& value)
    {
        m_Uniforms[name] = value;
    }

    // --- Texture Slot Handlers ---
    void Material::SetTexture(uint32_t slot, const std::shared_ptr<Texture>& texture)
    {
        SetTexture("u_Texture" + std::to_string(slot), slot, texture);
    }

    void Material::SetTexture(
        const std::string& uniformName, uint32_t slot, const std::shared_ptr<Texture>& texture)
    {
        m_Textures[slot] = {uniformName, slot, texture};
    }

    std::shared_ptr<Texture> Material::GetTexture(uint32_t slot) const
    {
        auto it = m_Textures.find(slot);
        return (it != m_Textures.end()) ? it->second.TexturePtr : nullptr;
    }

    void Material::SetBaseColorTexture(const std::shared_ptr<Texture>& texture)
    {
        SetTexture(
            "u_BaseColorTexture", static_cast<uint32_t>(MaterialTextureSlot::Albedo), texture);
    }

    void Material::SetNormalTexture(const std::shared_ptr<Texture>& texture)
    {
        SetTexture("u_NormalTexture", static_cast<uint32_t>(MaterialTextureSlot::Normal), texture);
    }

    void Material::SetMetallicRoughnessTexture(const std::shared_ptr<Texture>& texture)
    {
        SetTexture("u_MetallicRoughnessTexture",
            static_cast<uint32_t>(MaterialTextureSlot::MetallicRoughness), texture);
    }

    void Material::SetEmissiveTexture(const std::shared_ptr<Texture>& texture)
    {
        SetTexture(
            "u_EmissiveTexture", static_cast<uint32_t>(MaterialTextureSlot::Emissive), texture);
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

    void Material::BindUniformsAndTextures(const std::shared_ptr<Shader>& shader) const
    {
        for (const auto& [name, val] : m_Uniforms)
        {
            std::visit([&shader, &name](auto&& arg)
            {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, int>)
                    shader->SetInt(name, arg);
                else if constexpr (std::is_same_v<T, float>)
                    shader->SetFloat(name, arg);
                else if constexpr (std::is_same_v<T, Vector2>)
                    shader->SetVec2(name, arg);
                else if constexpr (std::is_same_v<T, Vector3>)
                    shader->SetVec3(name, arg);
                else if constexpr (std::is_same_v<T, Vector4>)
                    shader->SetVec4(name, arg);
                else if constexpr (std::is_same_v<T, Matrix4>)
                    shader->SetMat4(name, arg);
            }, val);
        }

        for (const auto& [slot, binding] : m_Textures)
        {
            if (binding.TexturePtr)
            {
                shader->SetInt(binding.UniformName, static_cast<int>(binding.Slot));
                binding.TexturePtr->Bind(binding.Slot);
            }
            else
            {
                shader->SetInt(binding.UniformName, static_cast<int>(binding.Slot));
                TextureLibrary::GetWhiteTexture()->Bind(binding.Slot);
            }
        }
    }

    void Material::Bind()
    {
        if (!m_shader)
            return;

        m_shader->Use();

        m_shader->SetVec4("u_BaseColor", BaseColor);
        m_shader->SetFloat("u_MetallicFactor", MetallicFactor);
        m_shader->SetFloat("u_RoughnessFactor", RoughnessFactor);
        m_shader->SetVec3("u_EmissiveFactor", EmissiveFactor);

        BindUniformsAndTextures(m_shader);
    }
} // namespace Aion