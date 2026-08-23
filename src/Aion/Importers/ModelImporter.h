#pragma once

#include <string>

namespace Aion
{
    class Object3D;

    class ModelImporter
    {
    public:
        static Object3D* Load(const std::string& path);
    };
} // namespace Aion