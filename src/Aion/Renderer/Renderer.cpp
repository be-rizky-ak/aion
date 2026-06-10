#include "Renderer.h"

#include <glad/glad.h>

#include <iostream>

#include "../Assets/Mesh.h"

#include "../Scene/Camera.h"
#include "../Scene/MeshRenderer.h"
#include "../Scene/Object3D.h"
#include "../Scene/Scene.h"

#include "../Renderer/Material.h"
#include "../Renderer/Shader.h"

#include "Shader.h"

Renderer::Renderer() : m_defaultShader(nullptr)
{
}

Renderer::~Renderer()
{
}

void Renderer::Init()
{
    glEnable(GL_DEPTH_TEST);

    const char* vertexSrc = R"(
        #version 330 core

        layout(location=0) in vec3 aPos;
        layout(location=1) in vec3 aNormal;
        layout(location=2) in vec2 aUV;

        uniform mat4 u_MVP;

        out vec2 v_UV;

        void main()
        {
            v_UV = aUV;
            gl_Position =
                u_MVP *
                vec4(aPos,1.0);
        }
    )";

    const char* fragmentSrc = R"(
        #version 330 core

        in vec2 v_UV;

        uniform sampler2D u_BaseColorTexture;
        uniform vec4 u_BaseColor;

        out vec4 FragColor;

        void main()
        {
            vec4 tex = 
                texture(
                    u_BaseColorTexture,
                    v_UV
                );

            FragColor = tex * u_BaseColor;
        }
    )";

    m_defaultShader = new Shader(vertexSrc, fragmentSrc);
}

void Renderer::Render(Scene* scene)
{
    Camera* camera = scene->GetActiveCamera();

    if (!camera)
    {
        return;
    }
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (Object3D* root : scene->GetObjects())
    {
        RenderObject(root, camera);
    }
}

void Renderer::RenderObject(Object3D* object, Camera* camera)
{
    if (!object)
    {
        return;
    }

    MeshRenderer* meshRenderer = object->GetComponent<MeshRenderer>();

    if (meshRenderer)
    {
        Material* material = meshRenderer->GetMaterial();

        Mesh* mesh = meshRenderer->GetMesh();

        if (mesh)
        {
            glm::mat4 model = object->GetWorldMatrix();

            glm::mat4 mvp = camera->GetProjectionMatrix() * camera->GetViewMatrix() * model;

            Shader* shader = m_defaultShader;
            if (material && material->GetShader())
            {
                shader = material->GetShader();
            }

            shader->Use();
            shader->SetVec4("u_BaseColor", material->BaseColor);
            shader->SetFloat("u_MetallicFactor", material->MetallicFactor);
            shader->SetFloat("u_RoughnessFactor", material->RoughnessFactor);
            shader->SetVec3("u_EmissiveFactor", material->EmissiveFactor);
            shader->SetMat4("u_MVP", mvp);
            shader->SetInt("u_BaseColorTexture", 0);
            shader->SetInt("u_NormalTexture", 1);
            shader->SetInt("u_MetallicRoughnessTexture", 2);
            shader->SetInt("u_EmissiveTexture", 3);

            if (material)
            {
                material->Bind();
            }

            mesh->Draw();
        }
    }

    for (Object3D* child : object->GetChildren())
    {
        RenderObject(child, camera);
    }
}

void Renderer::Shutdown()
{
}

Shader* Renderer::GetDefaultShader() const
{
    return m_defaultShader;
}

void Renderer::OnResize(uint32_t width, uint32_t height)
{
    glViewport(0, 0, width, height);
}