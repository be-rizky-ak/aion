#include "Renderer.h"
#include "Shader.h"
#include "Camera.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Static resources (temporary for simplicity)
static Shader* s_Shader = nullptr;
static Camera* s_Camera = nullptr;
static unsigned int s_MVPLocation = 0;

void Renderer::Init()
{
    // ===== SHADERS =====
    const char* vertexShaderSrc = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;

    uniform mat4 u_MVP;

    void main()
    {
        gl_Position = u_MVP * vec4(aPos, 1.0);
    }
    )";

    const char* fragmentShaderSrc = R"(
    #version 330 core
    out vec4 FragColor;

    void main()
    {
        FragColor = vec4(0.8, 0.4, 0.2, 1.0);
    }
    )";

    s_Shader = new Shader(vertexShaderSrc, fragmentShaderSrc);

    // Cache uniform location (important optimization)
    s_MVPLocation = glGetUniformLocation(s_Shader->GetID(), "u_MVP");

    // ===== CAMERA =====
    s_Camera = new Camera(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);

    // Enable depth testing for 3D
    glEnable(GL_DEPTH_TEST);

    // ===== CUBE GEOMETRY =====
    float vertices[] = {
        // back face
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        // front face
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        // left
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

        // right
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        // bottom
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        // top
        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f
    };

    // ===== BUFFERS =====
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind (good practice)
    glBindVertexArray(0);
}

void Renderer::Draw()
{
    // Clear screen
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    s_Shader->Use();

    // Rotate cube over time
    static float angle = 0.0f;
    angle += 0.5f;

    glm::mat4 model = glm::rotate(glm::mat4(1.0f),
        glm::radians(angle),
        glm::vec3(0.5f, 1.0f, 0.0f));

    glm::mat4 mvp =
        s_Camera->GetProjectionMatrix() *
        s_Camera->GetViewMatrix() *
        model;

    glUniformMatrix4fv(s_MVPLocation, 1, GL_FALSE, &mvp[0][0]);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Renderer::Shutdown()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    delete s_Shader;
    delete s_Camera;
}