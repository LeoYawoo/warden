#pragma once

#include <cstdint>
#include <cstddef>

// Reverse engineered from Warcraft III binary
// CDataAllocator manages memory allocation for data stores

class CDataAllocator {
public:
    CDataAllocator();
    ~CDataAllocator();

    // Allocate memory
    void* Allocate(size_t size);

    // Free memory
    void Free(void* ptr);

    // Reallocate memory
    void* Reallocate(void* ptr, size_t newSize);

    // Get total allocated memory
    size_t GetTotalAllocated() const;

    // Get allocation count
    size_t GetAllocationCount() const;

    // Reset allocator
    void Reset();

private:
    size_t m_totalAllocated;
    size_t m_allocationCount;
};
