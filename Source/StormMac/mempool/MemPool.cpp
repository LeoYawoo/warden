#include "MemPool.h"
#include "MemChunk.h"

// Reverse engineered from Warcraft III binary

MemPool::MemPool() : m_blockSize(0), m_unk3(0), m_unk5(0) {
}

void MemPool::Init(size_t blockSize, size_t a2) {
    m_blockSize = blockSize;
    m_unk3 = a2;
    m_unk5 = 0;
}

void* MemPool::MemAlloc() {
    // Try to allocate from existing chunks
    for (uint32_t i = 0; i < m_memchunks.Count(); i++) {
        MemChunk* chunk = m_memchunks[i];
        if (chunk) {
            void* ptr = chunk->MemAlloc();
            if (ptr) {
                return ptr;
            }
        }
    }

    // Create new chunk
    MemChunk* newChunk = new MemChunk(m_blockSize, m_unk3);
    uint32_t newCount = m_memchunks.Count() + 1;
    m_memchunks.SetCount(newCount);
    m_memchunks[newCount - 1] = newChunk;
    return newChunk->MemAlloc();
}

int32_t MemPool::MemFree(void* ptr) {
    if (!ptr) {
        return 0;
    }

    // Find which chunk contains this pointer
    for (uint32_t i = 0; i < m_memchunks.Count(); i++) {
        MemChunk* chunk = m_memchunks[i];
        if (chunk && chunk->Contains(ptr)) {
            chunk->MemFree(ptr);
            return 1;
        }
    }

    return 0;
}
