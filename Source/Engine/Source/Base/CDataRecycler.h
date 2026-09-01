#pragma once

#include <cstdint>
#include <cstddef>

// Reverse engineered from Warcraft III binary
// Address: 0x7479480
// CDataRecycler manages recycling of data buffers

class CDataRecycler {
public:
    CDataRecycler();
    ~CDataRecycler();

    // Get and resize data buffer
    void* GetAndResizeData(size_t newSize, void*& data, size_t& alloc,
                          const char* fileName, int lineNumber);

    // Return data to recycler
    void ReturnData(void* data, size_t size);

    // Get total recycled memory
    size_t GetTotalRecycled() const;

    // Get recycled buffer count
    size_t GetRecycledCount() const;

    // Clear recycler
    void Clear();

private:
    struct RecycledBuffer {
        void* data;
        size_t size;
        RecycledBuffer* next;
    };

    RecycledBuffer* m_freeList;
    size_t m_totalRecycled;
    size_t m_recycledCount;
};
