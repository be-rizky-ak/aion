#pragma once

class Shader
{
public:
    Shader(const char* vertexSrc, const char* fragmentSrc);
    ~Shader();

    void Use() const;

    unsigned int GetID() const { return m_ID; }

private:
    unsigned int m_ID;
};