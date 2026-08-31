#include "CDataStore.h"
#include <algorithm>

CDataStore::CDataStore()
    : m_vtable(nullptr)
    , m_data(nullptr)
    , m_dataSize(0)
    , m_usedSize(0)
    , m_capacity(0)
    , m_position(0)
    , m_state(-1) {
}

CDataStore::~CDataStore() {
    Destroy();
}

void CDataStore::Reset() {
    if (m_state == -1) {
        m_usedSize = 0;
        m_state = 0;
    }
    m_position = 0;
    m_state = -1;
}

void CDataStore::Destroy() {
    if (m_data) {
        delete[] m_data;
        m_data = nullptr;
    }
    m_dataSize = 0;
    m_usedSize = 0;
    m_capacity = 0;
    m_position = 0;
    m_state = -1;
}

bool CDataStore::Write(const void* data, uint32_t size) {
    if (!data || size == 0) {
        return false;
    }

    if (m_usedSize + size > m_capacity) {
        // 重新分配内存
        uint32_t newCapacity = std::max(m_capacity * 2, m_usedSize + size);
        uint8_t* newData = new uint8_t[newCapacity];

        if (m_data) {
            std::memcpy(newData, m_data, m_usedSize);
            delete[] m_data;
        }

        m_data = newData;
        m_capacity = newCapacity;
    }

    std::memcpy(m_data + m_usedSize, data, size);
    m_usedSize += size;
    return true;
}

bool CDataStore::Read(void* buffer, uint32_t size) {
    if (!buffer || size == 0 || !CanRead(size)) {
        return false;
    }

    std::memcpy(buffer, m_data + m_position, size);
    m_position += size;
    return true;
}

bool CDataStore::Skip(uint32_t bytes) {
    if (!CanRead(bytes)) {
        return false;
    }

    m_position += bytes;
    return true;
}

bool CDataStore::Seek(uint32_t position) {
    if (position > m_usedSize) {
        return false;
    }

    m_position = position;
    return true;
}
