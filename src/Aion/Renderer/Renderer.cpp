#include "Renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"
#include "Material.h"
#include "Shader.h"
#include "Texture.h"
#include "../Assets/Mesh.h"
#include "../Assets/Model.h"
#include "../Scene/Transform.h"

// Static resources (temporary for simplicity)
static Shader* s_Shader = nullptr;
static Camera* s_Camera = nullptr;

static unsigned int s_MVPLocation = 0;

static float s_LastX = 400.0f;
static float s_LastY = 300.0f;
static bool s_FirstMouse = true;

static Model* s_Model = nullptr;

void Renderer::Init()
{
    // ===== SHADERS =====
    const char* vertexShaderSrc = R"(
   #version 330 core

    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aNormal;
    layout (location = 2) in vec2 aUV;

    uniform mat4 u_MVP;

    out vec2 v_UV;

    void main()
    {
        v_UV = aUV;

        gl_Position = u_MVP * vec4(aPos, 1.0);
    }  
    )";

    const char* fragmentShaderSrc = R"(
    #version 330 core
    
    out vec4 FragColor;

    in vec2 v_UV;

    uniform sampler2D u_Texture;

    void main()
    {
        FragColor = texture(u_Texture, v_UV);
    }
    )";

    s_Shader = new Shader(vertexShaderSrc, fragmentShaderSrc);

    s_Model = new Model("assets/models/DamagedHelmet.glb");

    // Cache uniform location (important optimization)
    s_MVPLocation = glGetUniformLocation(s_Shader->GetID(), "u_MVP");

    // ===== CAMERA =====
    s_Camera = new Camera(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);

    // Enable depth testing for 3D
    glEnable(GL_DEPTH_TEST);
}

void Renderer::Draw()
{
    // Clear screen
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    s_Shader->Use();

    glm::mat4 model = glm::mat4(1.0f);

    glm::mat4 mvp =
        s_Camera->GetProjectionMatrix() *
        s_Camera->GetViewMatrix() *
        model;

    s_Shader->SetMat4(
        "u_MVP",
        mvp
    );

    if (s_Model->GetTexture())
    {
        s_Model->GetTexture()->Bind(0);
    }

    s_Shader->SetInt("u_Texture", 0);

    s_Model->Draw();
}

void Renderer::Update(float deltaTime, GLFWwindow* window)
{
    // ===== KEYBOARD =====

    bool forward =
        glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;

    bool backward =
        glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;

    bool left =
        glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;

    bool right =
        glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;

    s_Camera->ProcessKeyboard(
        deltaTime,
        forward,
        backward,
        left,
        right
    );

    // ===== MOUSE =====

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        double mouseX;
        double mouseY;

        glfwGetCursorPos(window, &mouseX, &mouseY);

        if (s_FirstMouse)
        {
            s_LastX = (float)mouseX;
            s_LastY = (float)mouseY;
            s_FirstMouse = false;
        }

        float xOffset = (float)mouseX - s_LastX;
        float yOffset = s_LastY - (float)mouseY;

        s_LastX = (float)mouseX;
        s_LastY = (float)mouseY;

        s_Camera->ProcessMouse(xOffset, yOffset);
    }
    else
    {
        // Reset first mouse when button released
        s_FirstMouse = true;
    }
}

void Renderer::Shutdown()
{    
    delete s_Shader;
    delete s_Camera;
    delete s_Model;
}