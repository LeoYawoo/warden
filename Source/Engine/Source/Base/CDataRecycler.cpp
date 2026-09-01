#include "CDataRecycler.h"
#include "StormMac/Memory.h"

// Reverse engineered from Warcraft III binary
// Address: 0x7479480

CDataRecycler::CDataRecycler() : m_freeList(nullptr), m_totalRecycled(0), m_recycledCount(0) {
}

CDataRecycler::~CDataRecycler() {
    Clear();
}

void* CDataRecycler::GetAndResizeData(size_t newSize, void*& data, size_t& alloc,
                                      const char* fileName, int lineNumber) {
    // Check if we have a recycled buffer of suitable size
    RecycledBuffer* prev = nullptr;
    RecycledBuffer* current = m_freeList;

    while (current) {
        if (current->size >= newSize) {
            // Found suitable buffer
            if (prev) {
                prev->next = current->next;
            } else {
                m_freeList = current->next;
            }

            void* result = current->data;
            m_totalRecycled -= current->size;
            m_recycledCount--;

            delete current;

            // Resize if needed
            if (alloc < newSize) {
                result = SMemReAlloc(result, newSize, fileName, lineNumber, 0);
                alloc = newSize;
            }

            data = static_cast<uint8_t*>(result);
            return result;
        }
        prev = current;
        current = current->next;
    }

    // No suitable buffer found, allocate new
    void* result = SMemAlloc(newSize, fileName, lineNumber, 0);
    if (result) {
        data = static_cast<uint8_t*>(result);
        alloc = newSize;
    }
    return result;
}

void CDataRecycler::ReturnData(void* data, size_t size) {
    if (data) {
        RecycledBuffer* buffer = new RecycledBuffer();
        buffer->data = data;
        buffer->size = size;
        buffer->next = m_freeList;
        m_freeList = buffer;

        m_totalRecycled += size;
        m_recycledCount++;
    }
}

size_t CDataRecycler::GetTotalRecycled() const {
    return m_totalRecycled;
}

size_t CDataRecycler::GetRecycledCount() const {
    return m_recycledCount;
}

void CDataRecycler::Clear() {
    while (m_freeList) {
        RecycledBuffer* buffer = m_freeList;
        m_freeList = m_freeList->next;

        SMemFree(buffer->data, __FILE__, __LINE__, 0);
        delete buffer;
    }
    m_totalRecycled = 0;
    m_recycledCount = 0;
}
