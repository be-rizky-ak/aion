#include "Renderer.h"

#include <glad/glad.h>

#include <iostream>

#include "../Assets/Mesh.h"

#include "../Scene/Camera.h"
#include "../Scene/CameraComponent.h"
#include "../Scene/MeshRenderer.h"
#include "../Scene/Object3D.h"
#include "../Scene/Scene.h"

#include "Material.h"
#include "RenderCommand.h"
#include "Shader.h"
#include "ShaderLibrary.h"

#include "Shader.h"

namespace Aion
{
    Renderer::Renderer() {}

    Renderer::~Renderer() {}

    void Renderer::Init()
    {
        glEnable(GL_DEPTH_TEST);

        ShaderLibrary::Init();
        RenderCommand::Init();
    }

    void Renderer::Render(Scene* scene)
    {
        CameraComponent* camera = scene->GetActiveCamera();

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

    void Renderer::RenderObject(Object3D* object, CameraComponent* camera)
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

                std::shared_ptr<Shader> shader = (material && material->GetShader())
                                                     ? material->GetShader()
                                                     : ShaderLibrary::GetDefault();

                if (shader)
                {
                    shader->Use();
                    shader->SetMat4("u_MVP", mvp);

                    if (material)
                    {
                        RenderCommand::ApplyState(material->State);
                        material->Bind();
                    }

                    mesh->Draw();
                }
            }
        }

        for (Object3D* child : object->GetChildren())
        {
            RenderObject(child, camera);
        }
    }

    void Renderer::Shutdown()
    {
        ShaderLibrary::Shutdown();
    }

    void Renderer::OnResize(uint32_t width, uint32_t height)
    {
        glViewport(0, 0, width, height);
    }
} // namespace Aion