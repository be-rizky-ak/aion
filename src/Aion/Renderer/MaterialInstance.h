#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include "Material.h"

namespace Aion
{
    class MaterialInstance : public Material
    {
    public:
        explicit MaterialInstance(const std::shared_ptr<Material>& parentMaterial);
        ~MaterialInstance() override = default;

        void Bind() override;

        std::shared_ptr<Material> GetParent() const { return m_parent; }
        void SetParent(const std::shared_ptr<Material>& parentMaterial)
        {
            m_parent = parentMaterial;
        }

        // Parameter Overrides
        void SetBaseColor(const Vector4& color);
        void SetMetallic(float metallic);
        void SetRoughness(float roughness);
        void SetEmissive(const Vector3& emissive);

        // Clear overrides to fallback back to parent values dynamically
        void ClearBaseColorOverride() { m_HasBaseColorOverride = false; }
        void ClearMetallicOverride() { m_HasMetallicOverride = false; }
        void ClearRoughnessOverride() { m_HasRoughnessOverride = false; }
        void ClearEmissiveOverride() { m_HasEmissiveOverride = false; }

    private:
        std::shared_ptr<Material> m_parent;

        bool m_HasBaseColorOverride = false;
        bool m_HasMetallicOverride = false;
        bool m_HasRoughnessOverride = false;
        bool m_HasEmissiveOverride = false;
    };
} // namespace Aion