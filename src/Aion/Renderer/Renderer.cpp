#include "Renderer.h"

#include <glad/glad.h>


#include "../Scene/Camera.h"
#include "../Scene/Scene.h"
#include "../Scene/MeshRenderer.h"

#include "Shader.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Init()
{
    glEnable(GL_DEPTH_TEST);
}

void Renderer::Render(
    Scene* scene,
    Camera* camera,
    Shader* shader)
{
    glClearColor(
        0.1f,
        0.1f,
        0.2f,
        1.0f
    );

    glClear(
        GL_COLOR_BUFFER_BIT |
        GL_DEPTH_BUFFER_BIT
    );

    shader->Use();

    for (Object3D* object :
        scene->GetObjects())
    {
        MeshRenderer* renderer =
            object->GetMeshRenderer();

        if (!renderer)
        {
            continue;
        }

        Material* material =
            renderer->GetMaterial();

        Mesh* mesh =
            renderer->GetMesh();

        if (!mesh)
        {
            continue;
        }

        glm::mat4 model =
            object
            ->Transform
            .GetMatrix();

        glm::mat4 mvp =
            camera->GetProjectionMatrix()
            *
            camera->GetViewMatrix()
            *
            model;

        shader->SetMat4(
            "u_MVP",
            mvp
        );

        if (material)
        {
            material->Bind();
        }

        mesh->Draw();
    }
}

void Renderer::Shutdown()
{
}