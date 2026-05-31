#pragma once

#include <string>

class Texture
{
public:
    Texture(unsigned char* data, int width, int height, int channels);
    ~Texture();

    void Bind(unsigned int slot = 0) const;

private:
    unsigned int m_TextureID;
};