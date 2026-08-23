#pragma once

#include <glm/glm.hpp>
#include <string>

namespace Aion
{
    class Shader
    {
    public:
        Shader(const char* vertexSrc, const char* fragmentSrc);
        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        ~Shader();

        void Use() const;

        void SetMat4(const std::string& name, const glm::mat4& matrix);
        void SetVec4(const std::string& name, const glm::vec4& value);
        void SetVec3(const std::string& name, const glm::vec3& value);
        void SetInt(const std::string& name, int value);
        void SetFloat(const std::string& name, float value);

        unsigned int GetID() const { return m_ID; }

    private:
        void Compile(const char* vertexSrc, const char* fragmentSrc);
        std::string ReadFile(const std::string& filepath);

        unsigned int m_ID;
    };
} // namespace Aion