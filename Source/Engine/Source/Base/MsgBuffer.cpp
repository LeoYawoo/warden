#include "MsgBuffer.h"

MsgBuffer::MsgBuffer()
    : m_size(0)
    , m_capacity(0)
    , m_position(0)
    , m_state(0) {
}

MsgBuffer::MsgBuffer(uint32_t initialSize)
    : m_data(initialSize)
    , m_size(0)
    , m_capacity(initialSize)
    , m_position(0)
    , m_state(0) {
}

MsgBuffer::~MsgBuffer() {
}

bool MsgBuffer::Write(const void* data, uint32_t size) {
    if (!data || size == 0) {
        return false;
    }

    if (m_size + size > m_capacity) {
        m_capacity = std::max(m_capacity * 2, m_size + size);
        m_data.resize(m_capacity);
    }

    std::memcpy(m_data.data() + m_size, data, size);
    m_size += size;
    return true;
}

bool MsgBuffer::Read(void* buffer, uint32_t size) {
    if (!buffer || size == 0 || !CanRead(size)) {
        return false;
    }

    std::memcpy(buffer, m_data.data() + m_position, size);
    m_position += size;
    return true;
}

bool MsgBuffer::Skip(uint32_t bytes) {
    if (!CanRead(bytes)) {
        return false;
    }

    m_position += bytes;
    return true;
}

bool MsgBuffer::Seek(uint32_t position) {
    if (position > m_size) {
        return false;
    }

    m_position = position;
    return true;
}

void MsgBuffer::Clear() {
    m_data.clear();
    m_size = 0;
    m_capacity = 0;
    m_position = 0;
}

void MsgBuffer::Reset() {
    m_size = 0;
    m_position = 0;
}
