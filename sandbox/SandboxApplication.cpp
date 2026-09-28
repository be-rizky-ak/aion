#include "SandboxApplication.h"

#include <cstring>
#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <stb_image_write.h>

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

static void SaveScreenshot(const char* filename, int width, int height)
{
    std::vector<unsigned char> pixels(width * height * 4);
    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
    std::vector<unsigned char> flipped(width * height * 4);
    for (int y = 0; y < height; ++y)
    {
        memcpy(&flipped[(height - 1 - y) * width * 4], &pixels[y * width * 4], width * 4);
    }
    stbi_write_png(filename, width, height, 4, flipped.data(), width * 4);
}

SandboxApplication::SandboxApplication() : Aion::Application({"Aion Sandbox", 1280, 720, true}) {}

SandboxApplication::~SandboxApplication() {}

void SandboxApplication::OnCreate()
{
    auto cameraObject = std::make_shared<Aion::Object3D>();
    auto cameraComponent = cameraObject->AddComponent<Aion::CameraComponent>(
        std::make_unique<Aion::PerspectiveCamera>(45.0f, 1280.0f / 720.0f, 0.1f, 100.0f));

    cameraObject->AddComponent<Aion::CameraControllerComponent>();

    cameraObject->Transform.Position = Aion::Vector3(0.0f, 0.0f, 5.0f);
    cameraObject->Transform.Rotation.y = 0.0f;

    GetScene()->Add(cameraObject);
    GetScene()->SetActiveCamera(cameraComponent);

    auto bird = Aion::ModelImporter::Load("assets/models/bird_orange.glb");
    bird->Transform.Position = Aion::Vector3(0.0f, 0.0f, 0.0f);
    GetScene()->Add(bird);
}

void SandboxApplication::OnUpdate()
{
    if (Aion::Input::GetKey(Aion::Key::F11))
    {
        bool isFullScreen = GetWindow()->IsFullscreen();
        GetWindow()->SetFullscreen(!isFullScreen);
    }

    GetRenderer()->Render(GetScene());

    static int frameCount = 0;
    frameCount++;
    if (frameCount == 10)
    {
        SaveScreenshot("/tmp/bird_anim_frame10.png", 1280, 720);
        std::cout << "Saved screenshot: /tmp/bird_anim_frame10.png" << std::endl;
    }
    if (frameCount == 60)
    {
        SaveScreenshot("/tmp/bird_anim_frame60.png", 1280, 720);
        std::cout << "Saved screenshot: /tmp/bird_anim_frame60.png" << std::endl;
    }
}