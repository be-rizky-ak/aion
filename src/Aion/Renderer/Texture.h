#pragma once

#include <string>

class Texture
{
  public:
    // Load from file
    Texture(const std::string& path);

    // Load from memory
    Texture(unsigned char* data, int width, int height, int channels);

    ~Texture();

    void Bind(unsigned int slot = 0) const;

    unsigned int GetID() const;

  private:
    void CreateTexture(unsigned char* data, int width, int height, int channels);

  private:
    unsigned int m_textureID;
};