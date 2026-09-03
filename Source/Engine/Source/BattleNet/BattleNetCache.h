#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>

// Reverse engineered from Warcraft III binary
// BattleNetCache manages Battle.net data caching

class BattleNetCache {
public:
    BattleNetCache();
    ~BattleNetCache();

    // Cache operations
    bool Add(const char* key, const void* data, uint32_t size);
    bool Get(const char* key, void* data, uint32_t size) const;
    bool Remove(const char* key);
    bool Has(const char* key) const;

    // Cache properties
    size_t GetCount() const;
    size_t GetTotalSize() const;

    // Cache management
    void Clear();
    void SetMaxSize(uint32_t maxSize);
    uint32_t GetMaxSize() const;

protected:
    struct CacheEntry {
        void* data;
        uint32_t size;
    };

    std::unordered_map<std::string, CacheEntry> m_cache;
    uint32_t m_maxSize;
    size_t m_totalSize;
};
