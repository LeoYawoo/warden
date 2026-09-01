#include "TInstanceCache.h"

// Reverse engineered from Warcraft III binary
// Address: 0x839B64

template<typename T>
TInstanceCache<T>::TInstanceCache(size_t initialSize)
    : m_capacity(initialSize) {
    m_instances.reserve(initialSize);
}

template<typename T>
TInstanceCache<T>::~TInstanceCache() {
    Clear();
}

template<typename T>
T* TInstanceCache<T>::Get(int index) {
    (void)index;
    auto instance = std::make_unique<T>();
    T* ptr = instance.get();
    m_instances.push_back(std::move(instance));
    return ptr;
}

template<typename T>
void TInstanceCache<T>::Clear() {
    m_instances.clear();
}

template<typename T>
size_t TInstanceCache<T>::GetCount() const {
    return m_instances.size();
}

template<typename T>
size_t TInstanceCache<T>::GetCapacity() const {
    return m_capacity;
}

// Explicit template instantiation
template class TInstanceCache<int>;
