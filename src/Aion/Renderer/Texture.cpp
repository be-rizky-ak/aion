#include "Texture.h"

#include <iostream>

#include <glad/glad.h>
#include <stb/stb_image.h>

Texture::Texture(const std::string& path)
{
    stbi_set_flip_vertically_on_load(true);

    int width;
    int height;
    int channels;

    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

    if (!data)
    {
        std::cout << "Failed to load texture: " << path << std::endl;

        return;
    }

    CreateTexture(data, width, height, channels);

    stbi_image_free(data);
}

Texture::Texture(unsigned char* data, int width, int height, int channels)
{
    CreateTexture(data, width, height, channels);
}

void Texture::CreateTexture(unsigned char* data, int width, int height, int channels)
{
    glGenTextures(1, &m_textureID);

    glBindTexture(GL_TEXTURE_2D, m_textureID);

    GLenum format = GL_RGB;

    switch (channels)
    {
    case 1:
        format = GL_RED;
        break;

    case 3:
        format = GL_RGB;
        break;

    case 4:
        format = GL_RGBA;
        break;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_textureID);
}

void Texture::Bind(unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);

    glBindTexture(GL_TEXTURE_2D, m_textureID);
}

unsigned int Texture::GetID() const
{
    return m_textureID;
}