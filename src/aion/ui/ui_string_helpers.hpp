#pragma once

#include "aion/string/string_utils.hpp"

namespace Aion
{
    namespace UI
    {
        // =========================================================================
        // Legacy UI String Helpers (Deprecated Forwarding Wrappers)
        // =========================================================================

        template <typename... Args>
        [[deprecated("UIFormatString is deprecated. Use Aion::String::Format instead.")]]
        inline std::string UIFormatString(const std::string& fmt, Args&&... args)
        {
            return Aion::String::Format(fmt, std::forward<Args>(args)...);
        }

        inline std::string UIFormatString(const char* fmt)
        {
            return Aion::String::Format(fmt);
        }

        template <typename T>
        [[deprecated("UIToString is deprecated. Use Aion::String::ToString instead.")]]
        inline std::string UIToString(const T& val)
        {
            return Aion::String::ToString(val);
        }

        template <typename... Args>
        [[deprecated("UIConcat is deprecated. Use Aion::String::Concat instead.")]]
        inline std::string UIConcat(Args&&... args)
        {
            return Aion::String::Concat(std::forward<Args>(args)...);
        }

    } // namespace UI
} // namespace Aion

// Legacy forwarding macros mapping to core string utilities:
#define UI_FORMAT_STRING(fmt, ...) Aion::String::Format((fmt), ##__VA_ARGS__)
#define UI_STRING_FORMAT(fmt, ...) Aion::String::Format((fmt), ##__VA_ARGS__)
#define UI_TO_STRING(val) Aion::String::ToString((val))
#define UI_STRING_CONCAT(...) Aion::String::Concat(__VA_ARGS__)

namespace aion
{
    namespace ui = ::Aion::UI;
}
