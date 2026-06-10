#include "SandboxApplication.h"

#include <iostream>

#include "Aion/Renderer/Material.h"
#include "Aion/Renderer/Renderer.h"
#include "Aion/Renderer/Shader.h"
#include "Aion/Renderer/Texture.h"

#include "Aion/Scene/CameraControllerComponent.h"
#include "Aion/Scene/MeshRenderer.h"
#include "Aion/Scene/Object3D.h"
#include "Aion/Scene/PerspectiveCamera.h"
#include "Aion/Scene/RotatorComponent.h"
#include "Aion/Scene/Scene.h"

#include "Aion/Assets/MeshFactory.h"

#include "Aion/Importers/ModelImporter.h"

SandboxApplication::SandboxApplication() : Application({"Aion Sandbox", 1280, 720, true})
{
}

SandboxApplication::~SandboxApplication()
{
}

void SandboxApplication::OnCreate()
{
    m_CameraObject = new Object3D();
    m_Camera = m_CameraObject->AddComponent<PerspectiveCamera>(45.0f, 1280.0f / 720.0f, 0.1f, 100.0f);
    m_CameraObject->AddComponent<CameraControllerComponent>();

    m_CameraObject->Transform.Position = glm::vec3(0.0f, 0.0f, 5.0f);

    m_CameraObject->Transform.Rotation.y = -90.0f;

    GetScene()->Add(m_CameraObject);
    GetScene()->SetActiveCamera(m_Camera);

    Object3D* helmetObject = ModelImporter::Load("assets/models/DamagedHelmet.glb");

    GetScene()->Add(helmetObject);

    // unsigned char pixels[] =
    // {
    //     255, 0, 0, 255,
    //     0, 255, 0, 255,
    //     0, 0, 255, 255,
    //     255,255,0,255
    // };

    // Texture* texture =
    //     new Texture(
    //         pixels,
    //         2,
    //         2,
    //         4
    //     );

    Texture* texture = new Texture("assets/textures/checker.png");

    Material* material = new Material();

    material->SetBaseColorTexture(texture);

    Mesh* cubeMesh = MeshFactory::CreateCube();

    Object3D* cube = new Object3D();

    cube->AddComponent<MeshRenderer>(cubeMesh, material);

    cube->AddComponent<RotatorComponent>();

    GetScene()->Add(cube);
}

void SandboxApplication::OnUpdate()
{
    GetRenderer()->Render(GetScene());
}