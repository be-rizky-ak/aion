#include "TextureLibrary.h"

namespace Aion
{
    void TextureLibrary::Init()
    {
        // Create 1x1 solid white default texture
        TextureSpecification whiteSpec;
        whiteSpec.Width = 1;
        whiteSpec.Height = 1;
        whiteSpec.Format = TextureFormat::RGBA8;
        whiteSpec.GenerateMipmaps = false;

        uint32_t whitePixel = 0xFFFFFFFF;
        s_WhiteTexture = std::make_shared<Texture>(whiteSpec, &whitePixel);

        // Create 2x2 magenta/black missing texture fallback
        TextureSpecification errorSpec;
        errorSpec.Width = 2;
        errorSpec.Height = 2;
        errorSpec.Format = TextureFormat::RGBA8;
        errorSpec.MinFilter = TextureFilter::Nearest;
        errorSpec.MagFilter = TextureFilter::Nearest;
        errorSpec.GenerateMipmaps = false;

        uint32_t errorPixels[4] = {0xFFFF00FF, 0xFF000000, 0xFF000000, 0xFFFF00FF};
        s_ErrorTexture = std::make_shared<Texture>(errorSpec, errorPixels);
    }

    void TextureLibrary::Shutdown()
    {
        s_Textures.clear();
        s_WhiteTexture.reset();
        s_ErrorTexture.reset();
    }

    std::shared_ptr<Texture> TextureLibrary::Load(const std::string& path, bool sRGB)
    {
        if (Exists(path))
        {
            return s_Textures[path];
        }

        auto texture = std::make_shared<Texture>(path, sRGB);
        if (!texture->IsLoaded())
        {
            return s_ErrorTexture;
        }

        s_Textures[path] = texture;
        return texture;
    }

    std::shared_ptr<Texture> TextureLibrary::LoadFromMemory(
        const std::string& name, const uint8_t* buffer, size_t length, bool sRGB)
    {
        if (Exists(name))
        {
            return s_Textures[name];
        }

        auto texture = std::make_shared<Texture>(buffer, length, sRGB);
        if (!texture->IsLoaded())
        {
            return s_ErrorTexture;
        }

        s_Textures[name] = texture;
        return texture;
    }

    std::shared_ptr<Texture> TextureLibrary::Get(const std::string& name)
    {
        if (Exists(name))
        {
            return s_Textures[name];
        }
        return s_ErrorTexture;
    }

    std::shared_ptr<Texture> TextureLibrary::GetWhiteTexture()
    {
        return s_WhiteTexture;
    }

    std::shared_ptr<Texture> TextureLibrary::GetErrorTexture()
    {
        return s_ErrorTexture;
    }

    bool TextureLibrary::Exists(const std::string& name)
    {
        return s_Textures.find(name) != s_Textures.end();
    }
} // namespace Aion