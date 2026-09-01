#include "FileCache.h"
#include "StormMac/Memory.h"
#include <cstdio>

// Reverse engineered from Warcraft III binary

FileCache::FileCache()
    : m_isOpen(false),
      m_position(0),
      m_fileSize(0),
      m_cacheHits(0),
      m_cacheMisses(0) {
}

FileCache::~FileCache() {
    Close();
}

bool FileCache::Open(const char* fileName) {
    if (m_isOpen) {
        Close();
    }

    m_fileName = fileName;
    m_isOpen = true;
    m_position = 0;

    // Get file size
    FILE* file = fopen(fileName, "rb");
    if (file) {
        fseek(file, 0, SEEK_END);
        m_fileSize = ftell(file);
        fclose(file);
    }

    return true;
}

void FileCache::Close() {
    ClearCache();
    m_isOpen = false;
    m_fileName.clear();
    m_position = 0;
    m_fileSize = 0;
}

size_t FileCache::Read(void* buffer, size_t size) {
    if (!m_isOpen || !buffer) {
        return 0;
    }

    size_t bytesRead = 0;
    size_t remaining = size;
    uint8_t* dest = static_cast<uint8_t*>(buffer);

    while (remaining > 0) {
        // Calculate cache block
        size_t blockIndex = m_position / CACHE_BLOCK_SIZE;
        size_t blockOffset = m_position % CACHE_BLOCK_SIZE;
        size_t bytesToRead = std::min(remaining, CACHE_BLOCK_SIZE - blockOffset);

        // Check cache
        auto it = m_cache.find(blockIndex);
        if (it != m_cache.end()) {
            // Cache hit
            memcpy(dest, it->second.data + blockOffset, bytesToRead);
            m_cacheHits++;
        } else {
            // Cache miss - read from file
            FILE* file = fopen(m_fileName.c_str(), "rb");
            if (file) {
                fseek(file, blockIndex * CACHE_BLOCK_SIZE, SEEK_SET);

                CacheEntry entry;
                entry.data = static_cast<uint8_t*>(SMemAlloc(CACHE_BLOCK_SIZE, __FILE__, __LINE__, 0));
                entry.size = fread(entry.data, 1, CACHE_BLOCK_SIZE, file);
                entry.offset = blockIndex * CACHE_BLOCK_SIZE;

                fclose(file);

                m_cache[blockIndex] = entry;
                m_cacheMisses++;

                memcpy(dest, entry.data + blockOffset, bytesToRead);
            } else {
                break;
            }
        }

        dest += bytesToRead;
        m_position += bytesToRead;
        bytesRead += bytesToRead;
        remaining -= bytesToRead;
    }

    return bytesRead;
}

size_t FileCache::Write(const void* buffer, size_t size) {
    // Write operations bypass cache
    (void)buffer;
    (void)size;
    return 0;
}

bool FileCache::Seek(long offset, int origin) {
    if (!m_isOpen) {
        return false;
    }

    long newPosition = m_position;
    switch (origin) {
        case SEEK_SET:
            newPosition = offset;
            break;
        case SEEK_CUR:
            newPosition = m_position + offset;
            break;
        case SEEK_END:
            newPosition = m_fileSize + offset;
            break;
        default:
            return false;
    }

    if (newPosition < 0 || newPosition > static_cast<long>(m_fileSize)) {
        return false;
    }

    m_position = newPosition;
    return true;
}

long FileCache::Tell() const {
    return m_position;
}

bool FileCache::IsOpen() const {
    return m_isOpen;
}

size_t FileCache::GetFileSize() const {
    return m_fileSize;
}

size_t FileCache::GetCacheHits() const {
    return m_cacheHits;
}

size_t FileCache::GetCacheMisses() const {
    return m_cacheMisses;
}

void FileCache::ClearCache() {
    for (auto& pair : m_cache) {
        SMemFree(pair.second.data, __FILE__, __LINE__, 0);
    }
    m_cache.clear();
    m_cacheHits = 0;
    m_cacheMisses = 0;
}
