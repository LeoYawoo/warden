#pragma once

#include <cstdint>
#include <string>

// Reverse engineered from Warcraft III binary
// SAPIExtend provides extended Storm API functions

namespace Storm {
    // Extended API functions
    bool Initialize();
    void Shutdown();

    // Memory functions
    void* Alloc(size_t size);
    void Free(void* ptr);
    void* Realloc(void* ptr, size_t size);

    // String functions
    size_t StrLen(const char* str);
    int32_t StrCmp(const char* str1, const char* str2);
    char* StrCopy(char* dest, const char* src, size_t destSize);

    // File functions
    bool FileExists(const char* fileName);
    size_t GetFileSize(const char* fileName);
}
