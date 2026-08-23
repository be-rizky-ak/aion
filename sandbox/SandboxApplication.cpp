#include "SandboxApplication.h"

#include <iostream>

#include "Aion/Core/Input.h"
#include "Aion/Core/KeyCodes.h"
#include "Aion/Core/Window.h"

#include "Aion/Math/Vector3.h"

#include "Aion/Renderer/Material.h"
#include "Aion/Renderer/Renderer.h"
#include "Aion/Renderer/Shader.h"
#include "Aion/Renderer/Texture.h"

#include "Aion/Scene/CameraComponent.h"
#include "Aion/Scene/CameraControllerComponent.h"
#include "Aion/Scene/MeshRenderer.h"
#include "Aion/Scene/Object3D.h"
#include "Aion/Scene/PerspectiveCamera.h"
#include "Aion/Scene/RotatorComponent.h"
#include "Aion/Scene/Scene.h"

#include "Aion/Assets/MeshFactory.h"

#include "Aion/Importers/ModelImporter.h"

SandboxApplication::SandboxApplication() : Aion::Application({"Aion Sandbox", 1280, 720, true}) {}

SandboxApplication::~SandboxApplication() {}

void SandboxApplication::OnCreate()
{
    m_CameraObject = new Aion::Object3D();
    m_CameraComponent = m_CameraObject->AddComponent<Aion::CameraComponent>(
        std::make_unique<Aion::PerspectiveCamera>(45.0f, 1280.0f / 720.0f, 0.1f, 100.0f));

    m_CameraObject->AddComponent<Aion::CameraControllerComponent>();

    m_CameraObject->Transform.Position = Aion::Vector3(0.0f, 0.0f, 5.0f);
    m_CameraObject->Transform.Rotation.y = 0.0f;

    GetScene()->Add(m_CameraObject);
    GetScene()->SetActiveCamera(m_CameraComponent);

    Aion::Object3D* helmetObject = Aion::ModelImporter::Load("assets/models/DamagedHelmet.glb");
    helmetObject->Transform.Position = Aion::Vector3(0.0f, 0.0f, 0.0f);

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

    Aion::Texture* texture = new Aion::Texture("assets/textures/checker.png");

    Aion::Material* material = new Aion::Material();

    material->SetBaseColorTexture(texture);

    Aion::Mesh* cubeMesh = Aion::MeshFactory::CreateCube();

    Aion::Object3D* cube = new Aion::Object3D();

    cube->AddComponent<Aion::MeshRenderer>(cubeMesh, material);

    cube->AddComponent<Aion::RotatorComponent>();
    cube->Transform.Position = Aion::Vector3(0.0f, 0.0f, 0.0f);

    // GetScene()->Add(cube);
}

void SandboxApplication::OnUpdate()
{
    if (Aion::Input::GetKey(Aion::Key::F11))
    {
        bool isFullScreen = GetWindow()->IsFullscreen();
        GetWindow()->SetFullscreen(!isFullScreen);
    }

    GetRenderer()->Render(GetScene());
}