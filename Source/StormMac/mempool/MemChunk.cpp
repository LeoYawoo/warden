#include "MemChunk.h"
#include "StormMac/Memory.h"

// Reverse engineered from Warcraft III binary

MemChunk::MemChunk(size_t blockSize, size_t a2)
    : m_memblocks(nullptr),
      m_free(nullptr),
      m_unk2(0),
      m_blockSize(blockSize),
      m_numBlocks(a2) {
    // Allocate memory blocks
    size_t totalSize = blockSize * a2;
    m_memblocks = SMemAlloc(totalSize, __FILE__, __LINE__, 0);

    if (m_memblocks) {
        // Initialize free list
        uint8_t* ptr = static_cast<uint8_t*>(m_memblocks);
        m_free = nullptr;

        for (size_t i = 0; i < a2; i++) {
            // Each block starts with a pointer to the next free block
            *reinterpret_cast<void**>(ptr) = m_free;
            m_free = ptr;
            ptr += blockSize;
        }
    }
}

bool MemChunk::Contains(void* ptr) {
    if (!m_memblocks || !ptr) {
        return false;
    }

    uint8_t* blockPtr = static_cast<uint8_t*>(m_memblocks);
    uint8_t* checkPtr = static_cast<uint8_t*>(ptr);

    return checkPtr >= blockPtr && checkPtr < blockPtr + (m_blockSize * m_numBlocks);
}

void* MemChunk::MemAlloc() {
    if (!m_free) {
        return nullptr;
    }

    // Get first free block
    void* ptr = m_free;

    // Update free list
    m_free = *reinterpret_cast<void**>(ptr);

    return ptr;
}

void MemChunk::MemFree(void* ptr) {
    if (!ptr) {
        return;
    }

    // Add block to free list
    *reinterpret_cast<void**>(ptr) = m_free;
    m_free = ptr;
}
