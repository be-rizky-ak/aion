#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT

#include "Model.h"

#include <iostream>

#include <glm/glm.hpp>
#include <tiny_gltf.h>

#include "Mesh.h"

#include "../Renderer/Material.h"
#include "../Renderer/Texture.h"

static Texture* GetTextureFromGLTF(int textureIndex, const tinygltf::Model& gltfModel,
                                   const std::vector<Texture*>& textures)
{
    if (textureIndex < 0)
    {
        return nullptr;
    }

    const tinygltf::Texture& gltfTexture = gltfModel.textures[textureIndex];

    int imageIndex = gltfTexture.source;

    if (imageIndex < 0 || imageIndex >= (int)textures.size())
    {
        return nullptr;
    }

    return textures[imageIndex];
}

Model::Model(const std::string& path)
{
    tinygltf::TinyGLTF loader;
    tinygltf::Model gltfModel;

    std::string error;
    std::string warning;

    bool result = false;

    bool isBinary = path.length() >= 4 && path.substr(path.length() - 4) == ".glb";

    if (isBinary)
    {
        result = loader.LoadBinaryFromFile(&gltfModel, &error, &warning, path);
    }
    else
    {
        result = loader.LoadASCIIFromFile(&gltfModel, &error, &warning, path);
    }

    if (!warning.empty())
    {
        std::cout << "GLTF Warning: " << warning << std::endl;
    }

    if (!error.empty())
    {
        std::cout << "GLTF Error: " << error << std::endl;
    }

    if (!result)
    {
        std::cout << "Failed to load GLTF: " << path << std::endl;

        return;
    }

    std::cout << "Loaded GLTF: " << path << std::endl;

    // ==========================================
    // TEXTURES
    // ==========================================

    for (const auto& image : gltfModel.images)
    {
        Texture* texture =
            new Texture(const_cast<unsigned char*>(image.image.data()), image.width, image.height, image.component);

        m_textures.push_back(texture);
    }

    // ==========================================
    // MATERIALS
    // ==========================================

    // std::vector<Material *> materials;

    for (const auto& gltfMaterial : gltfModel.materials)
    {
        Material* material = new Material();

        // int textureIndex =
        //     gltfMaterial
        //         .pbrMetallicRoughness
        //         .baseColorTexture
        //         .index;

        // if (textureIndex >= 0)
        // {
        //     const tinygltf::Texture &
        //         gltfTexture =
        //             gltfModel.textures[textureIndex];

        //     int imageIndex =
        //         gltfTexture.source;

        //     if (
        //         imageIndex >= 0 &&
        //         imageIndex <
        //             (int)m_textures.size())
        //     {
        //         material
        //             ->SetBaseColorTexture(
        //                 m_textures[imageIndex]);
        //     }
        // }

        // materials.push_back(
        //     material);

        const auto& pbr = gltfMaterial.pbrMetallicRoughness;
        if (pbr.baseColorFactor.size() == 4)
        {
            material->BaseColor = glm::vec4((float)pbr.baseColorFactor[0], (float)pbr.baseColorFactor[1],
                                            (float)pbr.baseColorFactor[2], (float)pbr.baseColorFactor[3]);
        }

        material->MetallicFactor = (float)pbr.metallicFactor;
        material->RoughnessFactor = (float)pbr.roughnessFactor;

        material->SetBaseColorTexture(GetTextureFromGLTF(pbr.baseColorTexture.index, gltfModel, m_textures));

        material->SetNormalTexture(GetTextureFromGLTF(gltfMaterial.normalTexture.index, gltfModel, m_textures));

        material->SetMetallicRoughnessTexture(
            GetTextureFromGLTF(pbr.metallicRoughnessTexture.index, gltfModel, m_textures));

        material->SetEmissiveTexture(GetTextureFromGLTF(gltfMaterial.emissiveTexture.index, gltfModel, m_textures));

        if (gltfMaterial.emissiveFactor.size() == 3)
        {
            material->EmissiveFactor =
                glm::vec3((float)gltfMaterial.emissiveFactor[0], (float)gltfMaterial.emissiveFactor[1],
                          (float)gltfMaterial.emissiveFactor[2]);
        }

        material->AlphaCutoff = (float)gltfMaterial.alphaCutoff;
        material->DoubleSided = gltfMaterial.doubleSided;

        if (gltfMaterial.alphaMode == "BLEND")
        {
            material->AlphaModeType = AlphaMode::Blend;
        }
        else if (gltfMaterial.alphaMode == "MASK")
        {
            material->AlphaModeType = AlphaMode::Mask;
        }
        else
        {
            material->AlphaModeType = AlphaMode::Opaque;
        }

        std::cout << "Material Loaded\n"
                  << "  BaseColorTexture: " << (material->GetBaseColorTexture() ? "Yes" : "No") << "\n"
                  << "  NormalTexture: " << (material->GetNormalTexture() ? "Yes" : "No") << "\n"
                  << "  MetallicRoughnessTexture: " << (material->GetMetallicRoughnessTexture() ? "Yes" : "No") << "\n"
                  << "  EmissiveTexture: " << (material->GetEmissiveTexture() ? "Yes" : "No") << "\n";

        m_materials.push_back(material);
    }

    // ==========================================
    // MESHES
    // ==========================================

    for (size_t meshIndex = 0; meshIndex < gltfModel.meshes.size(); meshIndex++)
    {
        const tinygltf::Mesh& gltfMesh = gltfModel.meshes[meshIndex];

        for (const tinygltf::Primitive& primitive : gltfMesh.primitives)
        {
            std::vector<Vertex> vertices;
            std::vector<uint32_t> indices;

            const float* positionBuffer = nullptr;

            const float* normalBuffer = nullptr;

            const float* uvBuffer = nullptr;

            int vertexCount = 0;

            // POSITION

            auto posIt = primitive.attributes.find("POSITION");

            if (posIt != primitive.attributes.end())
            {
                const tinygltf::Accessor& accessor = gltfModel.accessors[posIt->second];

                const tinygltf::BufferView& view = gltfModel.bufferViews[accessor.bufferView];

                positionBuffer = reinterpret_cast<const float*>(
                    &gltfModel.buffers[view.buffer].data[accessor.byteOffset + view.byteOffset]);

                vertexCount = (int)accessor.count;
            }

            // NORMAL

            auto normalIt = primitive.attributes.find("NORMAL");

            if (normalIt != primitive.attributes.end())
            {
                const tinygltf::Accessor& accessor = gltfModel.accessors[normalIt->second];

                const tinygltf::BufferView& view = gltfModel.bufferViews[accessor.bufferView];

                normalBuffer = reinterpret_cast<const float*>(
                    &gltfModel.buffers[view.buffer].data[accessor.byteOffset + view.byteOffset]);
            }

            // UV

            auto uvIt = primitive.attributes.find("TEXCOORD_0");

            if (uvIt != primitive.attributes.end())
            {
                const tinygltf::Accessor& accessor = gltfModel.accessors[uvIt->second];

                const tinygltf::BufferView& view = gltfModel.bufferViews[accessor.bufferView];

                uvBuffer = reinterpret_cast<const float*>(
                    &gltfModel.buffers[view.buffer].data[accessor.byteOffset + view.byteOffset]);
            }

            // VERTICES

            for (int i = 0; i < vertexCount; i++)
            {
                Vertex vertex;

                vertex.Position =
                    glm::vec3(positionBuffer[i * 3 + 0], positionBuffer[i * 3 + 1], positionBuffer[i * 3 + 2]);

                vertex.Normal =
                    normalBuffer ? glm::vec3(normalBuffer[i * 3 + 0], normalBuffer[i * 3 + 1], normalBuffer[i * 3 + 2])
                                 : glm::vec3(0.0f, 1.0f, 0.0f);

                vertex.UV = uvBuffer ? glm::vec2(uvBuffer[i * 2 + 0], uvBuffer[i * 2 + 1]) : glm::vec2(0.0f);

                vertices.push_back(vertex);
            }

            // INDICES

            if (primitive.indices >= 0)
            {
                const tinygltf::Accessor& accessor = gltfModel.accessors[primitive.indices];

                const tinygltf::BufferView& view = gltfModel.bufferViews[accessor.bufferView];

                const unsigned char* data = &gltfModel.buffers[view.buffer].data[accessor.byteOffset + view.byteOffset];

                for (size_t i = 0; i < accessor.count; i++)
                {
                    uint32_t index = 0;

                    switch (accessor.componentType)
                    {
                    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
                        index = ((uint8_t*)data)[i];
                        break;

                    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
                        index = ((uint16_t*)data)[i];
                        break;

                    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
                        index = ((uint32_t*)data)[i];
                        break;
                    }

                    indices.push_back(index);
                }
            }

            Mesh* mesh = new Mesh(vertices, indices);

            Material* material = nullptr;

            if (primitive.material >= 0 && primitive.material < (int)m_materials.size())
            {
                material = m_materials[primitive.material];
            }

            ModelPrimitive modelPrimitive;

            modelPrimitive.Mesh = mesh;

            modelPrimitive.Material = material;

            modelPrimitive.NodeIndex = -1;

            m_primitives.push_back(modelPrimitive);
        }
    }
}

Model::~Model()
{
    for (auto& primitive : m_primitives)
    {
        delete primitive.Mesh;
    }

    for (Material* material : m_materials)
    {
        delete material;
    }

    for (Texture* texture : m_textures)
    {
        delete texture;
    }
}

const std::vector<Texture*>& Model::GetTextures() const
{
    return m_textures;
}

const std::vector<ModelPrimitive>& Model::GetPrimitives() const
{
    return m_primitives;
}