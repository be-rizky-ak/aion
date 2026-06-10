#pragma once

#include <string>
#include <vector>

class Mesh;
class Material;
class Texture;

struct ModelPrimitive
{
    Mesh* Mesh;
    Material* Material;

    int NodeIndex;
};

class Model
{
  public:
    Model(const std::string& path);

    ~Model();

    const std::vector<Texture*>& GetTextures() const;

    const std::vector<ModelPrimitive>& GetPrimitives() const;

  private:
    std::vector<ModelPrimitive> m_primitives;
    std::vector<Texture*> m_textures;
    std::vector<Material*> m_materials;
};