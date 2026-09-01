#pragma once

#include <cstdint>
#include <vector>
#include <algorithm>

// Reverse engineered from Warcraft III binary
// Address: 0x9F2576
// CPropArrayList manages a list of properties

// Property structure
struct PROPARRAY {
    uint32_t id;
    uint32_t value;
    uint32_t flags;
};

// Template class for property array list
template<typename T>
class CPropArrayList {
public:
    CPropArrayList();
    ~CPropArrayList();

    // Add property
    void Add(const T& prop);

    // Remove property
    void Remove(uint32_t id);

    // Find property by ID
    T* Find(uint32_t id);

    // Find best matches
    void FindBestMatches(uint32_t count, const uint32_t* ids, int* results, int maxResults);

    // Get count
    size_t GetCount() const;

    // Get property by index
    T* GetByIndex(size_t index);

    // Clear all properties
    void Clear();

private:
    std::vector<T> m_properties;
};

// Implementation
template<typename T>
CPropArrayList<T>::CPropArrayList() {
}

template<typename T>
CPropArrayList<T>::~CPropArrayList() {
    Clear();
}

template<typename T>
void CPropArrayList<T>::Add(const T& prop) {
    m_properties.push_back(prop);
}

template<typename T>
void CPropArrayList<T>::Remove(uint32_t id) {
    m_properties.erase(
        std::remove_if(m_properties.begin(), m_properties.end(),
            [id](const T& p) { return p.id == id; }),
        m_properties.end()
    );
}

template<typename T>
T* CPropArrayList<T>::Find(uint32_t id) {
    for (auto& prop : m_properties) {
        if (prop.id == id) {
            return &prop;
        }
    }
    return nullptr;
}

template<typename T>
void CPropArrayList<T>::FindBestMatches(uint32_t count, const uint32_t* ids, int* results, int maxResults) {
    (void)count;
    (void)ids;
    (void)results;
    (void)maxResults;
}

template<typename T>
size_t CPropArrayList<T>::GetCount() const {
    return m_properties.size();
}

template<typename T>
T* CPropArrayList<T>::GetByIndex(size_t index) {
    if (index < m_properties.size()) {
        return &m_properties[index];
    }
    return nullptr;
}

template<typename T>
void CPropArrayList<T>::Clear() {
    m_properties.clear();
}

// Explicit template instantiation
template class CPropArrayList<PROPARRAY>;
