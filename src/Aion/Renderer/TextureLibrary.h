#pragma once

#include "Texture.h"
#include <memory>
#include <string>
#include <unordered_map>

namespace Aion
{
    class TextureLibrary
    {
    public:
        static void Init();
        static void Shutdown();

        static std::shared_ptr<Texture> Load(const std::string& path, bool sRGB = false);
        static std::shared_ptr<Texture> LoadFromMemory(
            const std::string& name, const uint8_t* buffer, size_t length, bool sRGB = false);

        static std::shared_ptr<Texture> Get(const std::string& name);
        static std::shared_ptr<Texture> GetWhiteTexture();
        static std::shared_ptr<Texture> GetErrorTexture();

        static bool Exists(const std::string& name);

    private:
        static inline std::unordered_map<std::string, std::shared_ptr<Texture>> s_Textures;
        static inline std::shared_ptr<Texture> s_WhiteTexture;
        static inline std::shared_ptr<Texture> s_ErrorTexture;
    };
} // namespace Aion