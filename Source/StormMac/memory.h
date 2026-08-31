#ifndef STORM_MEMORY_HPP
#define STORM_MEMORY_HPP

#include <cstdint>
#include <cstdlib>

void *SMemAlloc(size_t bytes, const char *filename, int32_t linenumber, uint32_t flags);

void SMemFree(void *ptr);

void SMemFree(void *ptr, const char *filename, int32_t linenumber, uint32_t flags);

void *SMemReAlloc(void *ptr, size_t bytes, const char *filename, int32_t linenumber, uint32_t flags);


namespace Blizzard {
    namespace Memory {

// Functions
        void *Allocate(uint32_t bytes);

        void *Allocate(uint32_t bytes, uint32_t flags, const char *filename, uint32_t linenumber, const char *a5);

        void Free(void *ptr);

    } // namespace Memory
} // namespace Blizzard
#endif
