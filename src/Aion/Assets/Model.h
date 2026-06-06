#pragma once

#include <vector>
#include <string>

#include "../Renderer/Texture.h"

class Mesh;
class Material;

class Model
{
public:
    Model(const std::string& path);
    ~Model();

    void Draw();

    Texture* GetTexture() const { return m_baseColorTexture; }

private:
    std::vector<Mesh*> m_meshes;
    std::vector<Material*> m_materials;
    
    Texture* m_baseColorTexture = nullptr;
};