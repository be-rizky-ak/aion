#pragma once

#include <glm/glm.hpp>

class Shader;
class Texture;

class Material
{
public:
    Material(Shader* shader);

    void Bind();

public:
    Shader* GetShader() const;

public:
    glm::vec3 Color;
    
    Texture* DiffuseTexture;

private:
    Shader* m_shader;
};