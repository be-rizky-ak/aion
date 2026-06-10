#pragma once

#include <string>

class Object3D;

class ModelImporter
{
  public:
    static Object3D* Load(const std::string& path);
};