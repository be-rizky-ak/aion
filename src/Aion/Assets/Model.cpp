#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT

#include "Model.h"

#include <iostream>

#include <tiny_gltf.h>
#include <glm/glm.hpp>

#include "Mesh.h"
#include "../Renderer/Material.h"
#include "../Renderer/Shader.h"


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
        result = loader.LoadBinaryFromFile(
            &gltfModel,
            &error,
            &warning,
            path
        );
    }
    else
    {
        result = loader.LoadASCIIFromFile(
            &gltfModel,
            &error,
            &warning,
            path
        );
    }

    if (!warning.empty())
    {
        std::cout << "GLTF Warning: " << warning << "\n";
    }

    if (!error.empty())
    {
        std::cout << "GLTF Error: " << error << "\n";
    }

    if (!result)
    {
        std::cout << "Failed to load GLTF: " << path << "\n";
        return;
    }

    std::cout << "Loaded GLTF: " << path << "\n";

    std::vector<Texture*> loadedTextures;

    for (const auto& image : gltfModel.images)
    {
        Texture* texture =
            new Texture(
                const_cast<unsigned char*>(image.image.data()),
                image.width,
                image.height,
                image.component
            );

        loadedTextures.push_back(texture);
    }

    if (!loadedTextures.empty())
    {
        m_BaseColorTexture = loadedTextures[0];
    }

    for (const tinygltf::Mesh& mesh : gltfModel.meshes)
    {
        for (const tinygltf::Primitive& primitive : mesh.primitives)
        {
            std::vector<Vertex> vertices;
            std::vector<uint32_t> indices;

            const float* positionBuffer = nullptr;
            const float* normalBuffer = nullptr;
            const float* uvBuffer = nullptr;

            int vertexCount = 0;

            // POSITION
            if (primitive.attributes.find("POSITION") != primitive.attributes.end())
            {
                const tinygltf::Accessor& accessor =
                    gltfModel.accessors[
                        primitive.attributes.find("POSITION")->second
                    ];

                const tinygltf::BufferView& view =
                    gltfModel.bufferViews[accessor.bufferView];

                positionBuffer = reinterpret_cast<const float*>(
                    &gltfModel.buffers[view.buffer]
                        .data[accessor.byteOffset + view.byteOffset]
                );

                vertexCount = accessor.count;
            }

            // NORMAL
            if (primitive.attributes.find("NORMAL") != primitive.attributes.end())
            {
                const tinygltf::Accessor& accessor =
                    gltfModel.accessors[
                        primitive.attributes.find("NORMAL")->second
                    ];

                const tinygltf::BufferView& view =
                    gltfModel.bufferViews[accessor.bufferView];

                normalBuffer = reinterpret_cast<const float*>(
                    &gltfModel.buffers[view.buffer]
                        .data[accessor.byteOffset + view.byteOffset]
                );
            }

            // UV
            if (primitive.attributes.find("TEXCOORD_0") != primitive.attributes.end())
            {
                const tinygltf::Accessor& accessor =
                    gltfModel.accessors[
                        primitive.attributes.find("TEXCOORD_0")->second
                    ];

                const tinygltf::BufferView& view =
                    gltfModel.bufferViews[accessor.bufferView];

                uvBuffer = reinterpret_cast<const float*>(
                    &gltfModel.buffers[view.buffer]
                        .data[accessor.byteOffset + view.byteOffset]
                );
            }

            for (int i = 0; i < vertexCount; i++)
            {
                Vertex vertex;

                vertex.Position = glm::vec3(
                    positionBuffer[i * 3 + 0],
                    positionBuffer[i * 3 + 1],
                    positionBuffer[i * 3 + 2]
                );

                if (normalBuffer)
                {
                    vertex.Normal = glm::vec3(
                        normalBuffer[i * 3 + 0],
                        normalBuffer[i * 3 + 1],
                        normalBuffer[i * 3 + 2]
                    );
                }

                if (uvBuffer)
                {
                    vertex.UV = glm::vec2(
                        uvBuffer[i * 2 + 0],
                        uvBuffer[i * 2 + 1]
                    );
                }

                vertices.push_back(vertex);
            }

            if (primitive.indices >= 0)
            {
                const tinygltf::Accessor& accessor =
                    gltfModel.accessors[primitive.indices];

                const tinygltf::BufferView& view =
                    gltfModel.bufferViews[accessor.bufferView];

                const unsigned char* data =
                    &gltfModel.buffers[view.buffer]
                        .data[accessor.byteOffset + view.byteOffset];

                for (size_t i = 0; i < accessor.count; i++)
                {
                    uint32_t index = 0;

                    switch (accessor.componentType)
                    {
                    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
                        index =
                            ((uint16_t*)data)[i];
                        break;

                    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
                        index =
                            ((uint32_t*)data)[i];
                        break;

                    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
                        index =
                            ((uint8_t*)data)[i];
                        break;
                    }

                    indices.push_back(index);
                }
            }

            std::cout << "Vertices: " << vertices.size() << " Indices: " << indices.size() << std::endl;

            Mesh* newMesh = new Mesh(vertices, indices);

            m_Meshes.push_back(newMesh);
        }
    }
}

void Model::Draw()
{
    for (size_t i = 0; i < m_Meshes.size(); i++)
    {
        if (i < m_Materials.size())
        {
            m_Materials[i]->Bind();
        }

        m_Meshes[i]->Draw();
    }
}

Model::~Model()
{
    for (Mesh* mesh : m_Meshes)
    {
        delete mesh;
    }

    for (Material* material : m_Materials)
    {
        delete material;
    }
}