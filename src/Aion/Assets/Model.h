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

    Texture* GetTexture() const { return m_BaseColorTexture; }

private:
    std::vector<Mesh*> m_Meshes;
    std::vector<Material*> m_Materials;
    
    Texture* m_BaseColorTexture = nullptr;
};