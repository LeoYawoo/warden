#include "AsyncFile.h"
#include <cstdio>

// Reverse engineered from Warcraft III binary

AsyncFile::AsyncFile()
    : m_open(false),
      m_pending(false),
      m_position(0),
      m_fileSize(0),
      m_handle(nullptr) {
}

AsyncFile::~AsyncFile() {
    Close();
}

bool AsyncFile::Open(const char* fileName, uint32_t mode) {
    if (!fileName) return false;

    Close();

    const char* modeStr = (mode & 1) ? "rb" : "rb";
    m_handle = fopen(fileName, modeStr);
    if (!m_handle) return false;

    m_fileName = fileName;
    m_open = true;
    m_position = 0;

    fseek(static_cast<FILE*>(m_handle), 0, SEEK_END);
    m_fileSize = ftell(static_cast<FILE*>(m_handle));
    fseek(static_cast<FILE*>(m_handle), 0, SEEK_SET);

    return true;
}

void AsyncFile::Close() {
    if (m_handle) {
        fclose(static_cast<FILE*>(m_handle));
        m_handle = nullptr;
    }
    m_open = false;
    m_position = 0;
    m_fileSize = 0;
}

bool AsyncFile::Read(void* buffer, uint32_t size, uint32_t* bytesRead) {
    if (!m_open || !buffer) return false;

    size_t read = fread(buffer, 1, size, static_cast<FILE*>(m_handle));
    m_position += static_cast<long>(read);

    if (bytesRead) *bytesRead = static_cast<uint32_t>(read);
    return read > 0;
}

bool AsyncFile::ReadAsync(void* buffer, uint32_t size) {
    return Read(buffer, size);
}

bool AsyncFile::Write(const void* buffer, uint32_t size, uint32_t* bytesWritten) {
    if (!m_open || !buffer) return false;

    size_t written = fwrite(buffer, 1, size, static_cast<FILE*>(m_handle));
    m_position += static_cast<long>(written);

    if (bytesWritten) *bytesWritten = static_cast<uint32_t>(written);
    return written > 0;
}

bool AsyncFile::WriteAsync(const void* buffer, uint32_t size) {
    return Write(buffer, size);
}

bool AsyncFile::Seek(long offset, int origin) {
    if (!m_open) return false;

    int result = fseek(static_cast<FILE*>(m_handle), offset, origin);
    if (result == 0) {
        m_position = ftell(static_cast<FILE*>(m_handle));
    }
    return result == 0;
}

long AsyncFile::Tell() const {
    return m_position;
}

const char* AsyncFile::GetFileName() const {
    return m_fileName.c_str();
}

bool AsyncFile::IsOpen() const {
    return m_open;
}

bool AsyncFile::IsEOF() const {
    if (!m_open) return true;
    return feof(static_cast<FILE*>(m_handle)) != 0;
}

uint32_t AsyncFile::GetFileSize() const {
    return m_fileSize;
}

bool AsyncFile::IsPending() const {
    return m_pending;
}

bool AsyncFile::Wait(uint32_t timeoutMs) {
    (void)timeoutMs;
    m_pending = false;
    return true;
}
