#pragma once

#include <glm/glm.hpp>
#include <string>

class Shader
{
  public:
    Shader(const char* vertexSrc, const char* fragmentSrc);
    ~Shader();

    void Use() const;

    void SetMat4(const std::string& name, const glm::mat4& matrix);
    void SetVec4(const std::string& name, const glm::vec4& value);
    void SetVec3(const std::string& name, const glm::vec3& value);
    void SetInt(const std::string& name, int value);
    void SetFloat(const std::string& name, float value);

    unsigned int GetID() const
    {
        return m_ID;
    }

  private:
    unsigned int m_ID;
};