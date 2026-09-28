#pragma once

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <memory>
#include <sstream>
#include <string>
#include <type_traits>

namespace Aion
{
    namespace String
    {
        // Core String Utility Traits
        template <typename T>
        inline std::string ToString(const T& value)
        {
            if constexpr (std::is_same_v<std::decay_t<T>, std::string>)
            {
                return value;
            }
            else if constexpr (std::is_same_v<std::decay_t<T>, const char*>)
            {
                return std::string(value);
            }
            else
            {
                std::ostringstream ss;
                ss << value;
                return ss.str();
            }
        }

        inline std::string Format(const char* format)
        {
            return std::string(format);
        }

        template <typename... Args>
        inline std::string Format(const std::string& fmt, Args&&... args)
        {
            int size_s = std::snprintf(nullptr, 0, fmt.c_str(), std::forward<Args>(args)...);
            if (size_s <= 0)
            {
                return "";
            }
            auto size = static_cast<size_t>(size_s) + 1;
            auto buf = std::make_unique<char[]>(size);
            std::snprintf(buf.get(), size, fmt.c_str(), std::forward<Args>(args)...);
            return std::string(buf.get(), buf.get() + size_s);
        }

        inline std::string Trim(const std::string& str)
        {
            auto start = str.find_first_not_of(" \t\n\r");
            if (start == std::string::npos) return "";
            auto end = str.find_last_not_of(" \t\n\r");
            return str.substr(start, end - start + 1);
        }

        inline std::string ToLower(const std::string& str)
        {
            std::string result = str;
            std::transform(result.begin(), result.end(), result.begin(),
                           [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
            return result;
        }

        inline std::string ToUpper(const std::string& str)
        {
            std::string result = str;
            std::transform(result.begin(), result.end(), result.begin(),
                           [](unsigned char c) { return static_cast<char>(std::toupper(c)); });
            return result;
        }

        template <typename... Args>
        inline std::string Concat(Args&&... args)
        {
            std::ostringstream ss;
            (ss << ... << std::forward<Args>(args));
            return ss.str();
        }

    } // namespace String
} // namespace Aion

namespace aion
{
    namespace string = ::Aion::String;
}
