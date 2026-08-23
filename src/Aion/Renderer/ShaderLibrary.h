#pragma once

#include <memory>
#include <string>
#include <unordered_map>

namespace Aion
{
    class Shader;

    class ShaderLibrary
    {
    public:
        static void Init();
        static void Shutdown();

        static void Add(const std::string& name, const std::shared_ptr<Shader>& shader);
        static std::shared_ptr<Shader> Get(const std::string& name);
        static std::shared_ptr<Shader> GetDefault();

    private:
        static std::unordered_map<std::string, std::shared_ptr<Shader>> s_Shaders;
        static std::shared_ptr<Shader> s_DefaultShader;
    };
} // namespace Aion