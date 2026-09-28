#pragma once

#include <algorithm>
#include <string>
#include <vector>

namespace Aion
{
    namespace Path
    {
        // Core Path Utility Traits
        inline std::string Normalize(const std::string& path)
        {
            if (path.empty())
                return "";

            std::string result = path;
            // Convert backslashes to forward slashes
            std::replace(result.begin(), result.end(), '\\', '/');

            // Collapse redundant slashes
            std::string collapsed;
            collapsed.reserve(result.size());
            bool lastWasSlash = false;
            for (size_t i = 0; i < result.size(); ++i)
            {
                char c = result[i];
                if (c == '/')
                {
                    if (!lastWasSlash)
                    {
                        collapsed += c;
                        lastWasSlash = true;
                    }
                }
                else
                {
                    collapsed += c;
                    lastWasSlash = false;
                }
            }

            // Clean trailing slash if not root
            if (collapsed.length() > 1 && collapsed.back() == '/')
            {
                collapsed.pop_back();
            }

            return collapsed;
        }

        inline std::string GetExtension(const std::string& path)
        {
            std::string norm = Normalize(path);
            auto dotPos = norm.find_last_of('.');
            auto slashPos = norm.find_last_of('/');
            if (dotPos != std::string::npos && (slashPos == std::string::npos || dotPos > slashPos))
            {
                return norm.substr(dotPos);
            }
            return "";
        }

        inline std::string GetFileName(const std::string& path)
        {
            std::string norm = Normalize(path);
            auto slashPos = norm.find_last_of('/');
            if (slashPos != std::string::npos)
            {
                return norm.substr(slashPos + 1);
            }
            return norm;
        }

        inline std::string Combine(const std::string& base, const std::string& relative)
        {
            if (base.empty()) return Normalize(relative);
            if (relative.empty()) return Normalize(base);

            std::string normBase = Normalize(base);
            std::string normRel = Normalize(relative);

            if (normRel.front() == '/')
            {
                normRel = normRel.substr(1);
            }

            return normBase + "/" + normRel;
        }

    } // namespace Path

    namespace IO
    {
        struct PathTraits
        {
            static inline std::string Normalize(const std::string& path) { return Path::Normalize(path); }
            static inline std::string GetExtension(const std::string& path) { return Path::GetExtension(path); }
            static inline std::string GetFileName(const std::string& path) { return Path::GetFileName(path); }
            static inline std::string Combine(const std::string& base, const std::string& relative) { return Path::Combine(base, relative); }
        };
    }
} // namespace Aion

namespace aion
{
    namespace path = ::Aion::Path;
}
