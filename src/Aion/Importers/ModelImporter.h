#pragma once

#include <memory>
#include <string>

namespace Aion
{
    class Object3D;

    class ModelImporter
    {
    public:
        static std::shared_ptr<Object3D> Load(const std::string& path);
    };
} // namespace Aion