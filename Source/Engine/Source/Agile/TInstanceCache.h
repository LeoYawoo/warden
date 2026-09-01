#pragma once

#include <cstddef>
#include <vector>
#include <memory>

// Reverse engineered from Warcraft III binary
// Address: 0x839B64
// TInstanceCache is a template class for caching instances

template<typename T>
class TInstanceCache {
public:
    TInstanceCache(size_t initialSize = 0);
    ~TInstanceCache();

    // Get an instance from cache or create new
    T* Get(int index = 0);

    // Clear all cached instances
    void Clear();

    // Get number of active instances
    size_t GetCount() const;

    // Get capacity
    size_t GetCapacity() const;

private:
    std::vector<std::unique_ptr<T>> m_instances;
    size_t m_capacity;
};
