#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT

#include "Model.h"

#include <iostream>

#include <tiny_gltf.h>

#include "Aion/Math/Matrix4.h"
#include "Aion/Math/Quaternion.h"
#include "Aion/Math/Vector2.h"
#include "Aion/Math/Vector3.h"
#include "Aion/Math/Vector4.h"

#include "Aion/Renderer/Material.h"
#include "Aion/Renderer/Texture.h"
#include "Mesh.h"

namespace Aion
{
    static std::shared_ptr<Texture> GetTextureFromGLTF(int textureIndex,
        const tinygltf::Model& gltfModel, const std::vector<std::shared_ptr<Texture>>& textures)
    {
        if (textureIndex < 0)
        {
            return nullptr;
        }

        const tinygltf::Texture& gltfTexture = gltfModel.textures[textureIndex];
        int imageIndex = gltfTexture.source;

        if (imageIndex < 0 || imageIndex >= static_cast<int>(textures.size()))
        {
            return nullptr;
        }

        return textures[imageIndex];
    }

    static Matrix4 GetNodeMatrix(const tinygltf::Node& node)
    {
        if (node.matrix.size() == 16)
        {
            Matrix4 mat;
            for (int col = 0; col < 4; ++col)
            {
                mat[col] = Vector4(static_cast<float>(node.matrix[col * 4 + 0]),
                    static_cast<float>(node.matrix[col * 4 + 1]),
                    static_cast<float>(node.matrix[col * 4 + 2]),
                    static_cast<float>(node.matrix[col * 4 + 3]));
            }
            return mat;
        }

        Vector3 translation(0.0f);
        if (node.translation.size() == 3)
        {
            translation = Vector3(static_cast<float>(node.translation[0]),
                static_cast<float>(node.translation[1]), static_cast<float>(node.translation[2]));
        }

        Quaternion rotation = Quaternion::Identity();
        if (node.rotation.size() == 4)
        {
            // tinygltf stores quaternions as [x, y, z, w]
            rotation = Quaternion(static_cast<float>(node.rotation[0]),
                static_cast<float>(node.rotation[1]), static_cast<float>(node.rotation[2]),
                static_cast<float>(node.rotation[3]));
        }

        Vector3 scale(1.0f);
        if (node.scale.size() == 3)
        {
            scale = Vector3(static_cast<float>(node.scale[0]), static_cast<float>(node.scale[1]),
                static_cast<float>(node.scale[2]));
        }

        return Matrix4::Translate(translation) * Matrix4::Rotate(rotation) * Matrix4::Scale(scale);
    }

    static std::shared_ptr<ModelNode> ProcessGLTFNode(const tinygltf::Model& gltfModel,
        int nodeIndex, const std::vector<std::shared_ptr<Material>>& materials)
    {
        const tinygltf::Node& gltfNode = gltfModel.nodes[nodeIndex];
        auto modelNode = std::make_shared<ModelNode>();
        modelNode->Name = gltfNode.name;

        if (gltfNode.matrix.size() == 16)
        {
            for (int col = 0; col < 4; ++col)
            {
                modelNode->LocalMatrix[col] =
                    Vector4(static_cast<float>(gltfNode.matrix[col * 4 + 0]),
                        static_cast<float>(gltfNode.matrix[col * 4 + 1]),
                        static_cast<float>(gltfNode.matrix[col * 4 + 2]),
                        static_cast<float>(gltfNode.matrix[col * 4 + 3]));
            }
        }
        else
        {
            if (gltfNode.translation.size() == 3)
            {
                modelNode->Translation = Vector3(static_cast<float>(gltfNode.translation[0]),
                    static_cast<float>(gltfNode.translation[1]),
                    static_cast<float>(gltfNode.translation[2]));
            }
            if (gltfNode.rotation.size() == 4)
            {
                modelNode->Rotation = Quaternion(static_cast<float>(gltfNode.rotation[0]),
                    static_cast<float>(gltfNode.rotation[1]),
                    static_cast<float>(gltfNode.rotation[2]),
                    static_cast<float>(gltfNode.rotation[3]));
            }
            if (gltfNode.scale.size() == 3)
            {
                modelNode->Scale = Vector3(static_cast<float>(gltfNode.scale[0]),
                    static_cast<float>(gltfNode.scale[1]), static_cast<float>(gltfNode.scale[2]));
            }

            modelNode->LocalMatrix = Matrix4::Translate(modelNode->Translation) *
                                     Matrix4::Rotate(modelNode->Rotation) *
                                     Matrix4::Scale(modelNode->Scale);
        }

        if (gltfNode.mesh >= 0 && gltfNode.mesh < static_cast<int>(gltfModel.meshes.size()))
        {
            const tinygltf::Mesh& gltfMesh = gltfModel.meshes[gltfNode.mesh];

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
                    positionBuffer = reinterpret_cast<const float*>(&gltfModel.buffers[view.buffer]
                            .data[accessor.byteOffset + view.byteOffset]);
                    vertexCount = static_cast<int>(accessor.count);
                }

                // NORMAL
                auto normalIt = primitive.attributes.find("NORMAL");
                if (normalIt != primitive.attributes.end())
                {
                    const tinygltf::Accessor& accessor = gltfModel.accessors[normalIt->second];
                    const tinygltf::BufferView& view = gltfModel.bufferViews[accessor.bufferView];
                    normalBuffer = reinterpret_cast<const float*>(&gltfModel.buffers[view.buffer]
                            .data[accessor.byteOffset + view.byteOffset]);
                }

                // UV
                auto uvIt = primitive.attributes.find("TEXCOORD_0");
                if (uvIt != primitive.attributes.end())
                {
                    const tinygltf::Accessor& accessor = gltfModel.accessors[uvIt->second];
                    const tinygltf::BufferView& view = gltfModel.bufferViews[accessor.bufferView];
                    uvBuffer = reinterpret_cast<const float*>(&gltfModel.buffers[view.buffer]
                            .data[accessor.byteOffset + view.byteOffset]);
                }

                vertices.reserve(vertexCount);
                for (int i = 0; i < vertexCount; i++)
                {
                    Vertex vertex;

                    vertex.Position = Vector3(positionBuffer[i * 3 + 0], positionBuffer[i * 3 + 1],
                        positionBuffer[i * 3 + 2]);

                    if (normalBuffer)
                    {
                        vertex.Normal = Vector3(normalBuffer[i * 3 + 0], normalBuffer[i * 3 + 1],
                            normalBuffer[i * 3 + 2])
                                            .Normalized();
                    }
                    else
                    {
                        vertex.Normal = Vector3(0.0f, 1.0f, 0.0f);
                    }

                    vertex.UV = uvBuffer ? Vector2(uvBuffer[i * 2 + 0], uvBuffer[i * 2 + 1])
                                         : Vector2(0.0f);

                    vertices.push_back(vertex);
                }

                // INDICES
                if (primitive.indices >= 0)
                {
                    const tinygltf::Accessor& accessor = gltfModel.accessors[primitive.indices];
                    const tinygltf::BufferView& view = gltfModel.bufferViews[accessor.bufferView];
                    const unsigned char* data =
                        &gltfModel.buffers[view.buffer].data[accessor.byteOffset + view.byteOffset];

                    indices.reserve(accessor.count);
                    for (size_t i = 0; i < accessor.count; i++)
                    {
                        uint32_t index = 0;
                        switch (accessor.componentType)
                        {
                        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
                            index = reinterpret_cast<const uint8_t*>(data)[i];
                            break;
                        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
                            index = reinterpret_cast<const uint16_t*>(data)[i];
                            break;
                        case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
                            index = reinterpret_cast<const uint32_t*>(data)[i];
                            break;
                        }
                        indices.push_back(index);
                    }
                }

                auto mesh = std::make_shared<Mesh>(vertices, indices);
                std::shared_ptr<Material> material = nullptr;

                if (primitive.material >= 0 &&
                    primitive.material < static_cast<int>(materials.size()))
                {
                    material = materials[primitive.material];
                }

                ModelPrimitive modelPrimitive;
                modelPrimitive.MeshPtr = mesh;
                modelPrimitive.MaterialPtr = material;
                modelNode->Primitives.push_back(modelPrimitive);
            }
        }

        for (int childIndex : gltfNode.children)
        {
            modelNode->Children.push_back(ProcessGLTFNode(gltfModel, childIndex, materials));
        }

        return modelNode;
    }

    Model::Model(const std::string& path)
    {
        tinygltf::TinyGLTF loader;
        tinygltf::Model gltfModel;
        std::string error;
        std::string warning;

        bool isBinary = path.length() >= 4 && path.substr(path.length() - 4) == ".glb";
        bool result = isBinary ? loader.LoadBinaryFromFile(&gltfModel, &error, &warning, path)
                               : loader.LoadASCIIFromFile(&gltfModel, &error, &warning, path);

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

        // Load Textures
        for (const auto& image : gltfModel.images)
        {
            TextureSpecification spec;
            spec.Width = image.width;
            spec.Height = image.height;

            switch (image.component)
            {
            case 1:
                spec.Format = TextureFormat::R8;
                break;
            case 3:
                spec.Format = TextureFormat::RGB8;
                break;
            case 4:
                spec.Format = TextureFormat::RGBA8;
                break;
            default:
                spec.Format = TextureFormat::RGBA8;
                break;
            }

            auto texture = std::make_shared<Texture>(spec, image.image.data());
            m_textures.push_back(texture);
        }

        // Load Materials
        for (const auto& gltfMaterial : gltfModel.materials)
        {
            auto material = std::make_shared<Material>();
            const auto& pbr = gltfMaterial.pbrMetallicRoughness;

            if (pbr.baseColorFactor.size() == 4)
            {
                material->BaseColor = Vector4(static_cast<float>(pbr.baseColorFactor[0]),
                    static_cast<float>(pbr.baseColorFactor[1]),
                    static_cast<float>(pbr.baseColorFactor[2]),
                    static_cast<float>(pbr.baseColorFactor[3]));
            }

            material->MetallicFactor = static_cast<float>(pbr.metallicFactor);
            material->RoughnessFactor = static_cast<float>(pbr.roughnessFactor);

            material->SetBaseColorTexture(
                GetTextureFromGLTF(pbr.baseColorTexture.index, gltfModel, m_textures));
            material->SetNormalTexture(
                GetTextureFromGLTF(gltfMaterial.normalTexture.index, gltfModel, m_textures));
            material->SetMetallicRoughnessTexture(
                GetTextureFromGLTF(pbr.metallicRoughnessTexture.index, gltfModel, m_textures));
            material->SetEmissiveTexture(
                GetTextureFromGLTF(gltfMaterial.emissiveTexture.index, gltfModel, m_textures));

            if (gltfMaterial.emissiveFactor.size() == 3)
            {
                material->EmissiveFactor =
                    Vector3(static_cast<float>(gltfMaterial.emissiveFactor[0]),
                        static_cast<float>(gltfMaterial.emissiveFactor[1]),
                        static_cast<float>(gltfMaterial.emissiveFactor[2]));
            }

            material->AlphaCutoff = static_cast<float>(gltfMaterial.alphaCutoff);
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

            m_materials.push_back(material);
        }

        // Scene Node Traversal
        if (!gltfModel.scenes.empty())
        {
            int sceneIndex = gltfModel.defaultScene >= 0 ? gltfModel.defaultScene : 0;
            const tinygltf::Scene& scene = gltfModel.scenes[sceneIndex];

            for (int nodeIndex : scene.nodes)
            {
                m_rootNodes.push_back(ProcessGLTFNode(gltfModel, nodeIndex, m_materials));
            }
        }
    }
} // namespace Aion