#include "CFStringUtilities.h"
#include <cstring>
#include <cstdlib>

// Reverse engineered from Warcraft III binary

namespace CFString {

std::string ToStdString(const void* cfString) {
    if (!cfString) return "";
    // Convert CFString to std::string
    // In a real implementation, this would handle CFString memory management
    return std::string(static_cast<const char*>(cfString));
}

void* FromStdString(const std::string& str) {
    // Create CFString from std::string
    // In a real implementation, this would allocate CFString memory
    // and copy the string data
    char* result = static_cast<char*>(malloc(str.size() + 1));
    if (result) {
        strcpy(result, str.c_str());
    }
    return result;
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
    if (!format) return nullptr;

    // Allocate buffer for formatted string
    char buffer[1024];

    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    // Create a copy of the string
    char* result = static_cast<char*>(malloc(strlen(buffer) + 1));
    if (result) {
        strcpy(result, buffer);
    }
    return result;
}

void ReleaseString(void* str) {
    if (str) {
        free(str);
    }
}

} // namespace CFString
