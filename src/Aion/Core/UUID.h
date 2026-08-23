#pragma once

#include <cstdint>
#include <functional>

namespace Aion
{
    class UUID
    {
    public:
        UUID();
        UUID(uint64_t uuid);
        UUID(const UUID&) = default;

        operator uint64_t() const { return m_uuid; }

    private:
        uint64_t m_uuid;
    };
} // namespace Aion

namespace std
{
    template <> struct hash<Aion::UUID>
    {
        std::size_t operator()(const Aion::UUID& uuid) const
        {
            return hash<uint64_t>()((uint64_t)uuid);
        }
    };
} // namespace std