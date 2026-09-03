#pragma once

#include <cstdint>
#include <string>

// Reverse engineered from Warcraft III binary
// CFStringUtilities provides Core Foundation string utilities

namespace CFString {
    // String conversion
    std::string ToStdString(const void* cfString);
    void* FromStdString(const std::string& str);

    // String operations
    bool IsEmpty(const void* cfString);
    size_t GetLength(const void* cfString);

    // String comparison
    int32_t Compare(const void* str1, const void* str2);
    int32_t CompareIgnoreCase(const void* str1, const void* str2);

    // String creation
    void* CreateString(const char* str);
    void* CreateStringWithFormat(const char* format, ...);

    // String release
    void ReleaseString(void* str);
}
