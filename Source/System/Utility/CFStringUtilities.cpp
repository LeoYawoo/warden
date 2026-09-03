#include "CFStringUtilities.h"
#include <cstring>
#include <cstdlib>

// Reverse engineered from Warcraft III binary

namespace CFString {

std::string ToStdString(const void* cfString) {
    if (!cfString) return "";
    // TODO: Implement actual CFString conversion
    return std::string(static_cast<const char*>(cfString));
}

void* FromStdString(const std::string& str) {
    // TODO: Implement actual CFString creation
    return const_cast<char*>(str.c_str());
}

bool IsEmpty(const void* cfString) {
    if (!cfString) return true;
    return static_cast<const char*>(cfString)[0] == '\0';
}

size_t GetLength(const void* cfString) {
    if (!cfString) return 0;
    return strlen(static_cast<const char*>(cfString));
}

int32_t Compare(const void* str1, const void* str2) {
    if (!str1 || !str2) return 0;
    return strcmp(static_cast<const char*>(str1), static_cast<const char*>(str2));
}

int32_t CompareIgnoreCase(const void* str1, const void* str2) {
    if (!str1 || !str2) return 0;
    return strcasecmp(static_cast<const char*>(str1), static_cast<const char*>(str2));
}

void* CreateString(const char* str) {
    if (!str) return nullptr;
    return const_cast<char*>(str);
}

void* CreateStringWithFormat(const char* format, ...) {
    (void)format;
    // TODO: Implement formatted string creation
    return nullptr;
}

void ReleaseString(void* str) {
    (void)str;
    // TODO: Implement string release
}

} // namespace CFString
