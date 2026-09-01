#pragma once

#include "CDataStore.h"
#include <vector>

// Forward declarations
class CDataAllocator;
class CDataRecycler;

// Reverse engineered from Warcraft III binary
// Address: 0x81D2BA
// CDataStoreChunked is a chunked data store implementation

class CDataStoreChunked : public CDataStore {
public:
    // Chunk structure
    struct Chunk {
        Chunk();
        ~Chunk();

        uint8_t* m_data;
        uint32_t m_size;
    };

    CDataStoreChunked();
    virtual ~CDataStoreChunked();

    // Override virtual functions
    virtual void InternalInitialize(uint8_t *&data, uint32_t &base, uint32_t &alloc) override;
    virtual void InternalDestroy(uint8_t *&data, uint32_t &base, uint32_t &alloc) override;
    virtual int32_t InternalFetchRead(uint32_t pos, uint32_t bytes, uint8_t *&data, uint32_t &base, uint32_t &alloc) override;
    virtual int32_t InternalFetchWrite(uint32_t pos, uint32_t bytes, uint8_t *&data, uint32_t &base, uint32_t &alloc,
                                       const char *fileName, int32_t lineNumber) override;

    // Chunk operations
    Chunk* AllocateChunk();
    void FreeChunk(Chunk* chunk);

    // Get chunk count
    size_t GetChunkCount() const;

    // Get chunk size
    uint32_t GetChunkSize() const;

    // Set chunk size
    void SetChunkSize(uint32_t size);

protected:
    std::vector<Chunk*> m_chunks;
    uint32_t m_chunkSize;
    CDataAllocator* m_allocator;
    CDataRecycler* m_recycler;
};
