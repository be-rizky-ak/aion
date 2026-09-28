#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include <glad/glad.h>

namespace Aion
{
    Shader::Shader(const char* vertexSrc, const char* fragmentSrc)
    {
        Compile(vertexSrc, fragmentSrc);
    }

    Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
    {
        std::string vertexCode = ReadFile(vertexPath);
        std::string fragmentCode = ReadFile(fragmentPath);
        Compile(vertexCode.c_str(), fragmentCode.c_str());
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_ID);
    }

    void Shader::Compile(const char* vertexSrc, const char* fragmentSrc)
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

    std::string Shader::ReadFile(const std::string& filepath)
    {
        std::ifstream file(filepath);
        if (!file.is_open())
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << filepath << std::endl;
            return "";
        }
        std::stringstream stream;
        stream << file.rdbuf();
        return stream.str();
    }

    void Shader::Use() const
    {
        glUseProgram(m_ID);
    }

    void Shader::SetInt(const std::string& name, int value)
    {
        GLint location = glGetUniformLocation(m_ID, name.c_str());
        glUniform1i(location, value);
    }

    void Shader::SetFloat(const std::string& name, float value)
    {
        GLint location = glGetUniformLocation(m_ID, name.c_str());
        glUniform1f(location, value);
    }

    void Shader::SetVec2(const std::string& name, const Vector2& value)
    {
        GLint location = glGetUniformLocation(m_ID, name.c_str());
        glUniform2f(location, value.x, value.y);
    }

    void Shader::SetVec3(const std::string& name, const Vector3& value)
    {
        GLint location = glGetUniformLocation(m_ID, name.c_str());
        glUniform3f(location, value.x, value.y, value.z);
    }

    void Shader::SetVec4(const std::string& name, const Vector4& value)
    {
        GLint location = glGetUniformLocation(m_ID, name.c_str());
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    void Shader::SetMat4(const std::string& name, const Matrix4& matrix)
    {
        GLint location = glGetUniformLocation(m_ID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, matrix.ValuePtr());
    }

    void Shader::SetMat4Array(const std::string& name, const std::vector<Matrix4>& matrices)
    {
        GLint location = glGetUniformLocation(m_ID, name.c_str());
        if (location != -1 && !matrices.empty())
        {
            glUniformMatrix4fv(location, static_cast<GLsizei>(matrices.size()), GL_FALSE, matrices[0].ValuePtr());
        }
    }
} // namespace Aion