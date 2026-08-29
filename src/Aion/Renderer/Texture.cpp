// src/Aion/Renderer/Texture.cpp
#include "Texture.h"

#include <glad/glad.h>
#include <iostream>
#include <stb/stb_image.h>

namespace Aion
{
    static GLenum TextureFormatToGLInternal(TextureFormat format)
    {
        switch (format)
        {
        case TextureFormat::R8:
            return GL_R8;
        case TextureFormat::RGB8:
            return GL_RGB8;
        case TextureFormat::RGBA8:
            return GL_RGBA8;
        case TextureFormat::SRGB8:
            return GL_SRGB8;
        case TextureFormat::SRGBA8:
            return GL_SRGB8_ALPHA8;
        case TextureFormat::Depth24Stencil8:
            return GL_DEPTH24_STENCIL8;
        default:
            return GL_NONE;
        }
    }

    static GLenum TextureFormatToGLDataFormat(TextureFormat format)
    {
        switch (format)
        {
        case TextureFormat::R8:
            return GL_RED;
        case TextureFormat::RGB8:
        case TextureFormat::SRGB8:
            return GL_RGB;
        case TextureFormat::RGBA8:
        case TextureFormat::SRGBA8:
            return GL_RGBA;
        case TextureFormat::Depth24Stencil8:
            return GL_DEPTH_STENCIL;
        default:
            return GL_NONE;
        }
    }

    static GLenum TextureWrapToGL(TextureWrap wrap)
    {
        switch (wrap)
        {
        case TextureWrap::Repeat:
            return GL_REPEAT;
        case TextureWrap::ClampToEdge:
            return GL_CLAMP_TO_EDGE;
        case TextureWrap::MirroredRepeat:
            return GL_MIRRORED_REPEAT;
        }
        return GL_REPEAT;
    }

    Texture::Texture(const std::string& path, bool sRGB) : m_path(path)
    {
        stbi_set_flip_vertically_on_load(true);

        int width, height, channels;
        stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

        if (!data)
        {
            std::cerr << "[Texture] Failed to load texture file: " << path << std::endl;
            return;
        }

        m_specification.Width = width;
        m_specification.Height = height;
        m_specification.Format = (channels == 4)
                                     ? (sRGB ? TextureFormat::SRGBA8 : TextureFormat::RGBA8)
                                     : (sRGB ? TextureFormat::SRGB8 : TextureFormat::RGB8);

        CreateGLTexture(data, channels);
        stbi_image_free(data);
        m_isLoaded = true;
    }

    Texture::Texture(const unsigned char* pixels, int width, int height, int channels)
    {
        m_specification.Width = width;
        m_specification.Height = height;

        switch (channels)
        {
        case 1:
            m_specification.Format = TextureFormat::R8;
            break;
        case 3:
            m_specification.Format = TextureFormat::RGB8;
            break;
        case 4:
            m_specification.Format = TextureFormat::RGBA8;
            break;
        default:
            m_specification.Format = TextureFormat::RGBA8;
            break;
        }

        CreateGLTexture(pixels, channels);
        m_isLoaded = (pixels != nullptr);
    }

    Texture::Texture(const uint8_t* memoryBuffer, size_t length, bool sRGB)
    {
        stbi_set_flip_vertically_on_load(true);

        int width, height, channels;
        stbi_uc* data = stbi_load_from_memory(
            memoryBuffer, static_cast<int>(length), &width, &height, &channels, 0);

        if (!data)
        {
            std::cerr << "[Texture] Failed to decode image from memory (embedded glTF texture)"
                      << std::endl;
            return;
        }

        m_specification.Width = width;
        m_specification.Height = height;
        m_specification.Format = (channels == 4)
                                     ? (sRGB ? TextureFormat::SRGBA8 : TextureFormat::RGBA8)
                                     : (sRGB ? TextureFormat::SRGB8 : TextureFormat::RGB8);

        CreateGLTexture(data, channels);
        stbi_image_free(data);
        m_isLoaded = true;
    }

    Texture::Texture(const TextureSpecification& spec, const void* data) : m_specification(spec)
    {
        CreateGLTexture(data, 4);
        m_isLoaded = (data != nullptr);
    }

    void Texture::CreateGLTexture(const void* data, int channels)
    {
        glGenTextures(1, &m_textureID);
        glBindTexture(GL_TEXTURE_2D, m_textureID);

        GLenum internalFormat = TextureFormatToGLInternal(m_specification.Format);
        GLenum dataFormat = TextureFormatToGLDataFormat(m_specification.Format);

        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_specification.Width,
            m_specification.Height, 0, dataFormat, GL_UNSIGNED_BYTE, data);

        if (m_specification.GenerateMipmaps)
        {
            glGenerateMipmap(GL_TEXTURE_2D);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        }
        else
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TextureWrapToGL(m_specification.WrapS));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TextureWrapToGL(m_specification.WrapT));
    }

    Texture::~Texture()
    {
        if (m_textureID)
        {
            glDeleteTextures(1, &m_textureID);
        }
    }

    void Texture::Bind(uint32_t slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_textureID);
    }
} // namespace Aion