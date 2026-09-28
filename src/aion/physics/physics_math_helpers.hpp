#pragma once

#include "aion/math/generic_math.hpp"

namespace Aion
{
    namespace Physics
    {
        // =========================================================================
        // Legacy Physics Math Helpers (Deprecated Wrappers)
        // =========================================================================

        [[deprecated("PhysicsVector3Lerp is deprecated. Use Aion::Math::Lerp instead.")]]
        inline Vector3 PhysicsVector3Lerp(const Vector3& a, const Vector3& b, float t)
        {
            return Aion::Math::Lerp(a, b, t);
        }

        [[deprecated("PhysicsVector2Lerp is deprecated. Use Aion::Math::Lerp instead.")]]
        inline Vector2 PhysicsVector2Lerp(const Vector2& a, const Vector2& b, float t)
        {
            return Aion::Math::Lerp(a, b, t);
        }

        template <typename T>
        [[deprecated("PhysicsLerp is deprecated. Use Aion::Math::Lerp instead.")]]
        inline T PhysicsLerp(const T& a, const T& b, float t)
        {
            return Aion::Math::Lerp(a, b, t);
        }

        template <typename T>
        [[deprecated("PhysicsClamp is deprecated. Use Aion::Math::Clamp instead.")]]
        inline T PhysicsClamp(T val, T minVal, T maxVal)
        {
            return Aion::Math::Clamp(val, minVal, maxVal);
        }

        [[deprecated("PhysicsVector3Clamp is deprecated. Use Aion::Math::Clamp instead.")]]
        inline Vector3 PhysicsVector3Clamp(const Vector3& v, const Vector3& minV, const Vector3& maxV)
        {
            return Aion::Math::Clamp(v, minV, maxV);
        }

    } // namespace Physics
} // namespace Aion

namespace aion
{
    namespace physics = ::Aion::Physics;
}
