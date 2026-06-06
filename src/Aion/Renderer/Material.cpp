#include "Material.h"

#include <glad/glad.h>

#include "Shader.h"
#include "Texture.h"

Material::Material(Shader* shader)
    : m_shader(shader)
    , Color(1.0f, 1.0f, 1.0f)
    , DiffuseTexture(nullptr)
{
}

void Material::Bind()
{
    m_shader->Use();

    m_shader->SetVec3("u_Color", Color);

    if (DiffuseTexture)
    {
        DiffuseTexture->Bind(0);

        unsigned int location =
            glGetUniformLocation(
                m_shader->GetID(),
                "u_Texture"
            );

        glUniform1i(location, 0);
    }
}

Shader* Material::GetShader() const
{
    return m_shader;
}