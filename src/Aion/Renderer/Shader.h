#pragma once

#include <string>
#include <glm/glm.hpp>

class Shader
{
public:
    Shader(const char* vertexSrc, const char* fragmentSrc);
    ~Shader();

    void Use() const;

    void SetMat4(const std::string& name, const glm::mat4& matrix);
    void SetVec3(const std::string& name, const glm::vec3& value);
    void SetInt(const std::string& name, int value);

    unsigned int GetID() const { return m_ID; }

private:
    unsigned int m_ID;
};