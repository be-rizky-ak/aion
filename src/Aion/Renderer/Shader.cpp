#include "Shader.h"

#include <iostream>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const char* vertexSrc, const char* fragmentSrc)
{
    // Vertex Shader
    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexSrc, nullptr);
    glCompileShader(vertex);

    int success;
    char infoLog[512];

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cout << "ERROR::VERTEX_SHADER_COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Fragment Shader
    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentSrc, nullptr);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::cout << "ERROR::FRAGMENT_SHADER_COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Shader Program
    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertex);
    glAttachShader(m_ID, fragment);
    glLinkProgram(m_ID);

    glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_ID, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER_PROGRAM_LINKING_FAILED\n" << infoLog << std::endl;
    }

    // Cleanup
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader()
{
    glDeleteProgram(m_ID);
}

void Shader::Use() const
{
    glUseProgram(m_ID);
}

void Shader::SetMat4(const std::string& name, const glm::mat4& matrix)
{
    unsigned int location = glGetUniformLocation(m_ID, name.c_str());

    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::SetVec4(const std::string& name, const glm::vec4& value)
{
    GLint location = glGetUniformLocation(m_ID, name.c_str());

    glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Shader::SetVec3(const std::string& name, const glm::vec3& value)
{
    unsigned int location = glGetUniformLocation(m_ID, name.c_str());

    glUniform3f(location, value.x, value.y, value.z);
}

void Shader::SetInt(const std::string& name, int value)
{
    unsigned int location = glGetUniformLocation(m_ID, name.c_str());

    glUniform1i(location, value);
}

void Shader::SetFloat(const std::string& name, float value)
{
    GLint location = glGetUniformLocation(m_ID, name.c_str());

    glUniform1f(location, value);
}