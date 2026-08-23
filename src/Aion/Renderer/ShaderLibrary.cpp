#include "ShaderLibrary.h"
#include "BuiltinShaders.h"
#include "Shader.h"

namespace Aion
{
    std::unordered_map<std::string, std::shared_ptr<Shader>> ShaderLibrary::s_Shaders;
    std::shared_ptr<Shader> ShaderLibrary::s_DefaultShader = nullptr;

    void ShaderLibrary::Init()
    {
        s_DefaultShader =
            std::make_shared<Shader>(Shaders::StandardVertex, Shaders::StandardFragment);

        s_Shaders["Standard"] = s_DefaultShader;
    }

    void ShaderLibrary::Shutdown()
    {
        s_Shaders.clear();
        s_DefaultShader.reset();
    }

    void ShaderLibrary::Add(const std::string& name, const std::shared_ptr<Shader>& shader)
    {
        s_Shaders[name] = shader;
    }

    std::shared_ptr<Shader> ShaderLibrary::Get(const std::string& name)
    {
        auto it = s_Shaders.find(name);
        if (it != s_Shaders.end())
            return it->second;

        return s_DefaultShader;
    }

    std::shared_ptr<Shader> ShaderLibrary::GetDefault()
    {
        return s_DefaultShader;
    }
} // namespace Aion