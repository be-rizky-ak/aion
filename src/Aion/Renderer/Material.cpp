#include "Material.h"

#include <glad/glad.h>

#include "Shader.h"
#include "Texture.h"

Material::Material(Shader* shader)
    : m_Shader(shader)
    , Color(1.0f, 1.0f, 1.0f)
    , DiffuseTexture(nullptr)
{
}

void Material::Bind()
{
    m_Shader->Use();

    m_Shader->SetVec3("u_Color", Color);

    if (DiffuseTexture)
    {
        DiffuseTexture->Bind(0);

        unsigned int location =
            glGetUniformLocation(
                m_Shader->GetID(),
                "u_Texture"
            );

        glUniform1i(location, 0);
    }
}

Shader* Material::GetShader() const
{
    return m_Shader;
}