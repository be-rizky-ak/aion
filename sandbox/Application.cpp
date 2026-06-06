#include "Application.h"

#include "Aion/Renderer/Renderer.h"
#include "Aion/Renderer/Shader.h"
#include "Aion/Renderer/Material.h"
#include "Aion/Renderer/Texture.h"

#include "Aion/Scene/Scene.h"
#include "Aion/Scene/Object3D.h"
#include "Aion/Scene/MeshRenderer.h"
#include "Aion/Scene/PerspectiveCamera.h"

#include "Aion/Assets/MeshFactory.h"

Application::Application()
    :
    m_window(
        1280,
        720,
        "Aion Sandbox"
    )
{
    m_scene = new Scene();
}

void Application::Run()
{
    Renderer renderer;

    renderer.Init();

    // ====================================
    // Camera
    // ====================================

    PerspectiveCamera camera(
        45.0f,
        1280.0f / 720.0f,
        0.1f,
        100.0f
    );

    camera.Transform.Position =
        glm::vec3(
            0.0f,
            0.0f,
            5.0f
        );

    // ====================================
    // Shader
    // ====================================

    const char* vertexShaderSrc = R"(
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
                vec4(aPos, 1.0);
        }
    )";

    const char* fragmentShaderSrc = R"(
        #version 330 core

        in vec2 v_UV;

        out vec4 FragColor;

        uniform sampler2D u_Texture;

        void main()
        {
            FragColor =
                texture(
                    u_Texture,
                    v_UV
                );
        }
    )";

    Shader shader(
        vertexShaderSrc,
        fragmentShaderSrc
    );

    // ====================================
    // Material
    // ====================================

    Material* material =
        new Material(
            &shader
        );

    material->DiffuseTexture =
        new Texture(
            "assets/textures/checker.png"
        );

    // ====================================
    // Mesh
    // ====================================

    Mesh* cubeMesh =
        MeshFactory::CreateCube();

    // ====================================
    // MeshRenderer
    // ====================================

    MeshRenderer* cubeRenderer =
        new MeshRenderer(
            cubeMesh,
            material
        );

    // ====================================
    // Object
    // ====================================

    Object3D* cube =
        new Object3D();

    cube->SetMeshRenderer(
        cubeRenderer
    );

    cube->Transform.Position =
        glm::vec3(
            0.0f,
            0.0f,
            0.0f
        );

    // ====================================
    // Scene
    // ====================================

    m_scene->Add(
        cube
    );

    // ====================================
    // Main Loop
    // ====================================

    while (!m_window.ShouldClose())
    {
        renderer.Render(
            m_scene,
            &camera,
            &shader
        );

        m_window.SwapBuffers();
        m_window.PollEvents();
    }

    // ====================================
    // Cleanup
    // ====================================

    renderer.Shutdown();

    delete cubeRenderer;
    delete cubeMesh;

    delete material->DiffuseTexture;
    delete material;

    delete cube;

    delete m_scene;
}