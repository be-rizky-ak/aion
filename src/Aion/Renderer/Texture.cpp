#include "Texture.h"

#include <iostream>

#include <glad/glad.h>
#include <stb/stb_image.h>

Texture::Texture( unsigned char* data, int width, int height, int channels)
{
    glGenTextures(1, &m_TextureID);

    glBindTexture(GL_TEXTURE_2D, m_TextureID);

    GLenum format = GL_RGB;

    if (channels == 1)
        format = GL_RED;
    else if (channels == 3)
        format = GL_RGB;
    else if (channels == 4)
        format = GL_RGBA;

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        format,
        width,
        height,
        0,
        format,
        GL_UNSIGNED_BYTE,
        data
    );

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER,
        GL_LINEAR_MIPMAP_LINEAR
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MAG_FILTER,
        GL_LINEAR
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_S,
        GL_REPEAT
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_T,
        GL_REPEAT
    );
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_TextureID);
}

void Texture::Bind(unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
}