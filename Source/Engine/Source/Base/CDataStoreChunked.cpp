#include "CDataStoreChunked.h"
#include "StormMac/Memory.h"

// Reverse engineered from Warcraft III binary
// Address: 0x81D2BA

CDataStoreChunked::Chunk::Chunk() : m_data(nullptr), m_size(0) {
}

CDataStoreChunked::Chunk::~Chunk() {
    if (m_data) {
        SMemFree(m_data, __FILE__, __LINE__, 0);
        m_data = nullptr;
    }
}

CDataStoreChunked::CDataStoreChunked()
    : CDataStore(),
      m_chunkSize(4096),
      m_allocator(nullptr),
      m_recycler(nullptr) {
}

CDataStoreChunked::~CDataStoreChunked() {
    // Clean up chunks
    for (auto* chunk : m_chunks) {
        delete chunk;
    }
    m_chunks.clear();
}

void CDataStoreChunked::InternalInitialize(uint8_t *&data, uint32_t &base, uint32_t &alloc) {
    (void)data;
    (void)base;
    (void)alloc;
}

void CDataStoreChunked::InternalDestroy(uint8_t *&data, uint32_t &base, uint32_t &alloc) {
    (void)data;
    (void)base;
    (void)alloc;
}

int32_t CDataStoreChunked::InternalFetchRead(uint32_t pos, uint32_t bytes, uint8_t *&data, uint32_t &base, uint32_t &alloc) {
    (void)pos;
    (void)bytes;
    (void)data;
    (void)base;
    (void)alloc;
    return 0;
}

int32_t CDataStoreChunked::InternalFetchWrite(uint32_t pos, uint32_t bytes, uint8_t *&data, uint32_t &base, uint32_t &alloc,
                                               const char *fileName, int32_t lineNumber) {
    (void)pos;
    (void)bytes;
    (void)data;
    (void)base;
    (void)alloc;
    (void)fileName;
    (void)lineNumber;
    return 0;
}

CDataStoreChunked::Chunk* CDataStoreChunked::AllocateChunk() {
    Chunk* chunk = new Chunk();
    chunk->m_data = static_cast<uint8_t*>(SMemAlloc(m_chunkSize, __FILE__, __LINE__, 0));
    chunk->m_size = 0;
    m_chunks.push_back(chunk);
    return chunk;
}

void CDataStoreChunked::FreeChunk(Chunk* chunk) {
    if (chunk) {
        delete chunk;
    }
}

size_t CDataStoreChunked::GetChunkCount() const {
    return m_chunks.size();
}

uint32_t CDataStoreChunked::GetChunkSize() const {
    return m_chunkSize;
}

void CDataStoreChunked::SetChunkSize(uint32_t size) {
    m_chunkSize = size;
}
