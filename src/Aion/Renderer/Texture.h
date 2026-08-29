#pragma once

#include <cstdint>
#include <memory>
#include <string>

namespace Aion
{
    enum class TextureFormat
    {
        None = 0,
        R8,
        RGB8,
        RGBA8,
        SRGB8,
        SRGBA8,
        Depth24Stencil8
    };

    enum class TextureFilter
    {
        Linear,
        Nearest,
        MipmapLinear
    };

    enum class TextureWrap
    {
        Repeat,
        ClampToEdge,
        MirroredRepeat
    };

    struct TextureSpecification
    {
        uint32_t Width = 1;
        uint32_t Height = 1;
        TextureFormat Format = TextureFormat::RGBA8;
        TextureFilter MinFilter = TextureFilter::MipmapLinear;
        TextureFilter MagFilter = TextureFilter::Linear;
        TextureWrap WrapS = TextureWrap::Repeat;
        TextureWrap WrapT = TextureWrap::Repeat;
        bool GenerateMipmaps = true;
    };

    class Texture
    {
    public:
        explicit Texture(const std::string& path, bool sRGB = false);

        Texture(const unsigned char* pixels, int width, int height, int channels);
        Texture(const uint8_t* memoryBuffer, size_t length, bool sRGB = false);
        Texture(const TextureSpecification& spec, const void* data = nullptr);

        ~Texture();

        void Bind(uint32_t slot = 0) const;

        uint32_t GetID() const { return m_textureID; }
        uint32_t GetWidth() const { return m_specification.Width; }
        uint32_t GetHeight() const { return m_specification.Height; }
        const std::string& GetPath() const { return m_path; }
        bool IsLoaded() const { return m_isLoaded; }

    private:
        void CreateGLTexture(const void* data, int channels);

    private:
        uint32_t m_textureID = 0;
        std::string m_path;
        TextureSpecification m_specification;
        bool m_isLoaded = false;
    };
} // namespace Aion