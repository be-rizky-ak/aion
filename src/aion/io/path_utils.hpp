#pragma once

#include "aion/path/path_utils.hpp"

namespace Aion
{
    namespace IO
    {
        // =========================================================================
        // Legacy IO Path Utilities (Deprecated Forwarding Wrappers)
        // =========================================================================

        [[deprecated("NormalizePath is deprecated. Use Aion::Path::Normalize instead.")]]
        inline std::string NormalizePath(const std::string& path)
        {
            return Aion::Path::Normalize(path);
        }

        [[deprecated("GetPathExtension is deprecated. Use Aion::Path::GetExtension instead.")]]
        inline std::string GetPathExtension(const std::string& path)
        {
            return Aion::Path::GetExtension(path);
        }

        [[deprecated("GetPathFileName is deprecated. Use Aion::Path::GetFileName instead.")]]
        inline std::string GetPathFileName(const std::string& path)
        {
            return Aion::Path::GetFileName(path);
        }

        [[deprecated("CombinePaths is deprecated. Use Aion::Path::Combine instead.")]]
        inline std::string CombinePaths(const std::string& base, const std::string& relative)
        {
            return Aion::Path::Combine(base, relative);
        }

    } // namespace IO
} // namespace Aion

namespace aion
{
    namespace io = ::Aion::IO;
}
