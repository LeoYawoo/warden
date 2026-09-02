#pragma once

#include <cstdint>
#include <string>

// Reverse engineered from Warcraft III binary
// AsyncFile manages asynchronous file operations

class AsyncFile {
public:
    AsyncFile();
    ~AsyncFile();

    // File operations
    bool Open(const char* fileName, uint32_t mode = 0);
    void Close();

    // Read operations
    bool Read(void* buffer, uint32_t size, uint32_t* bytesRead = nullptr);
    bool ReadAsync(void* buffer, uint32_t size);

    // Write operations
    bool Write(const void* buffer, uint32_t size, uint32_t* bytesWritten = nullptr);
    bool WriteAsync(const void* buffer, uint32_t size);

    // File position
    bool Seek(long offset, int origin);
    long Tell() const;

    // File properties
    const char* GetFileName() const;
    bool IsOpen() const;
    bool IsEOF() const;
    uint32_t GetFileSize() const;

    // Async operations
    bool IsPending() const;
    bool Wait(uint32_t timeoutMs = 0xFFFFFFFF);

protected:
    std::string m_fileName;
    bool m_open;
    bool m_pending;
    long m_position;
    uint32_t m_fileSize;
    void* m_handle;
};
