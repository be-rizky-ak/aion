#include "Renderer.h"

#include <glad/glad.h>

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

        m_RenderQueue.Clear();

        for (const auto& root : scene->GetObjects())
        {
            if (root)
            {
                SubmitObject(root.get(), camera);
            }
        }

        m_RenderQueue.Sort();

        ExecuteCommands(m_RenderQueue.GetOpaqueQueue(), camera);
        ExecuteCommands(m_RenderQueue.GetTransparentQueue(), camera);
    }

    void Renderer::SubmitObject(Object3D* object, CameraComponent* camera)
    {
        if (!object)
        {
            return;
        }

        MeshRenderer* meshRenderer = object->GetComponent<MeshRenderer>();
        if (meshRenderer && meshRenderer->GetMesh())
        {
            Matrix4 model = object->GetWorldMatrix();
            Vector4 modelVec = model[3];

            Vector3 objectPos = Vector3(modelVec.x, modelVec.y, modelVec.z);
            Vector3 cameraPos = camera->GetPosition();
            float distance = (cameraPos - objectPos).Length();

            m_RenderQueue.Submit(
                meshRenderer->GetMesh(), meshRenderer->GetMaterial(), model, distance);
        }

        for (const auto& child : object->GetChildren())
        {
            SubmitObject(child.get(), camera);
        }
    }

    void Renderer::ExecuteCommands(
        const std::vector<DrawCommand>& commands, CameraComponent* camera)
    {
        if (!camera)
        {
            return;
        }

        Matrix4 viewProj = camera->GetProjectionMatrix() * camera->GetViewMatrix();

        for (const auto& cmd : commands)
        {
            if (!cmd.MeshPtr)
            {
                continue;
            }

            Shader* shader = nullptr;

            if (cmd.MaterialPtr && cmd.MaterialPtr->GetShader())
            {
                shader = cmd.MaterialPtr->GetShader().get();
            }
            else
            {
                const auto& defaultShader = ShaderLibrary::GetDefault();
                shader = defaultShader ? defaultShader.get() : nullptr;
            }

            if (shader)
            {
                Matrix4 mvp = viewProj * cmd.Transform;

                shader->Use();
                shader->SetMat4("u_MVP", mvp);

                if (cmd.MaterialPtr)
                {
                    Aion::RenderCommand::ApplyState(cmd.MaterialPtr->State);
                    cmd.MaterialPtr->Bind();
                }

                cmd.MeshPtr->Draw();
            }
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