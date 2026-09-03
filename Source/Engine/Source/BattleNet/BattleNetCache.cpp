#include "BattleNetCache.h"
#include "StormMac/Memory.h"
#include <cstring>

// Reverse engineered from Warcraft III binary

BattleNetCache::BattleNetCache() : m_maxSize(0xFFFFFFFF), m_totalSize(0) {}
BattleNetCache::~BattleNetCache() { Clear(); }

bool BattleNetCache::Add(const char* key, const void* data, uint32_t size) {
    if (!key || !data || size == 0) return false;

    // Remove existing entry if present
    Remove(key);

    // Check max size
    if (m_totalSize + size > m_maxSize) return false;

    void* buffer = SMemAlloc(size, __FILE__, __LINE__, 0);
    if (!buffer) return false;

    memcpy(buffer, data, size);
    m_cache[key] = {buffer, size};
    m_totalSize += size;
    return true;
}

bool BattleNetCache::Get(const char* key, void* data, uint32_t size) const {
    if (!key || !data) return false;

    auto it = m_cache.find(key);
    if (it == m_cache.end()) return false;

    uint32_t copySize = (size < it->second.size) ? size : it->second.size;
    memcpy(data, it->second.data, copySize);
    return true;
}

bool BattleNetCache::Remove(const char* key) {
    if (!key) return false;

    auto it = m_cache.find(key);
    if (it == m_cache.end()) return false;

    SMemFree(it->second.data, __FILE__, __LINE__, 0);
    m_totalSize -= it->second.size;
    m_cache.erase(it);
    return true;
}

bool BattleNetCache::Has(const char* key) const {
    if (!key) return false;
    return m_cache.find(key) != m_cache.end();
}

size_t BattleNetCache::GetCount() const {
    return m_cache.size();
}

size_t BattleNetCache::GetTotalSize() const {
    return m_totalSize;
}

void BattleNetCache::Clear() {
    for (auto& pair : m_cache) {
        SMemFree(pair.second.data, __FILE__, __LINE__, 0);
    }
    m_cache.clear();
    m_totalSize = 0;
}

void BattleNetCache::SetMaxSize(uint32_t maxSize) {
    m_maxSize = maxSize;
}

uint32_t BattleNetCache::GetMaxSize() const {
    return m_maxSize;
}
