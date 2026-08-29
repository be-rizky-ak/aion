#pragma once

#include <string>

#include "Aion/Math/Matrix4.h"
#include "Aion/Math/Vector2.h"
#include "Aion/Math/Vector3.h"
#include "Aion/Math/Vector4.h"

namespace Aion
{
    class Shader
    {
    public:
        Shader(const char* vertexSrc, const char* fragmentSrc);
        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        ~Shader();

        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;

        Shader(Shader&&) noexcept = default;
        Shader& operator=(Shader&&) noexcept = default;

        void Use() const;

        void SetInt(const std::string& name, int value);
        void SetFloat(const std::string& name, float value);
        void SetVec2(const std::string& name, const Vector2& value);
        void SetVec3(const std::string& name, const Vector3& value);
        void SetVec4(const std::string& name, const Vector4& value);
        void SetMat4(const std::string& name, const Matrix4& matrix);

        unsigned int GetID() const { return m_ID; }

    private:
        void Compile(const char* vertexSrc, const char* fragmentSrc);
        std::string ReadFile(const std::string& filepath);

        unsigned int m_ID;
    };
} // namespace Aion