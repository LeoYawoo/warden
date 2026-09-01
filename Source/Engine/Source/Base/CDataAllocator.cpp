#include "CDataAllocator.h"
#include "StormMac/Memory.h"

// Reverse engineered from Warcraft III binary

CDataAllocator::CDataAllocator() : m_totalAllocated(0), m_allocationCount(0) {
}

CDataAllocator::~CDataAllocator() {
    Reset();
}

void* CDataAllocator::Allocate(size_t size) {
    void* ptr = SMemAlloc(size, __FILE__, __LINE__, 0);
    if (ptr) {
        m_totalAllocated += size;
        m_allocationCount++;
    }
    return ptr;
}

void CDataAllocator::Free(void* ptr) {
    if (ptr) {
        SMemFree(ptr, __FILE__, __LINE__, 0);
        m_allocationCount--;
    }
}

void* CDataAllocator::Reallocate(void* ptr, size_t newSize) {
    void* newPtr = SMemReAlloc(ptr, newSize, __FILE__, __LINE__, 0);
    if (newPtr) {
        m_totalAllocated = m_totalAllocated - (ptr ? 0 : 0) + newSize;
    }
    return newPtr;
}

size_t CDataAllocator::GetTotalAllocated() const {
    return m_totalAllocated;
}

size_t CDataAllocator::GetAllocationCount() const {
    return m_allocationCount;
}

void CDataAllocator::Reset() {
    m_totalAllocated = 0;
    m_allocationCount = 0;
}
