#pragma once

#include <cstdint>
#include <cstddef>
#include <string>
#include <unordered_map>

// Reverse engineered from Warcraft III binary
// FileCache provides caching for file operations

class FileCache {
public:
    FileCache();
    ~FileCache();

    // Open file
    bool Open(const char* fileName);

    // Close file
    void Close();

    // Read data
    size_t Read(void* buffer, size_t size);

    // Write data
    size_t Write(const void* buffer, size_t size);

    // Seek to position
    bool Seek(long offset, int origin);

    // Get current position
    long Tell() const;

    // Check if file is open
    bool IsOpen() const;

    // Get file size
    size_t GetFileSize() const;

    // Get cache hit count
    size_t GetCacheHits() const;

    // Get cache miss count
    size_t GetCacheMisses() const;

    // Clear cache
    void ClearCache();

private:
    struct CacheEntry {
        uint8_t* data;
        size_t size;
        size_t offset;
    };

    std::string m_fileName;
    bool m_isOpen;
    long m_position;
    size_t m_fileSize;

    std::unordered_map<size_t, CacheEntry> m_cache;
    size_t m_cacheHits;
    size_t m_cacheMisses;

    static const size_t CACHE_BLOCK_SIZE = 4096;
};
