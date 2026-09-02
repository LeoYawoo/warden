#include "NetProviderLOOP.h"

// Reverse engineered from Warcraft III binary

NetProviderLOOP::NetProviderLOOP() : m_connected(false), m_buffer(nullptr), m_bufferSize(0) {
    m_providerType = PROVIDER_LOOP;
    m_providerName = "Loopback";
}

NetProviderLOOP::~NetProviderLOOP() { Shutdown(); }

bool NetProviderLOOP::Initialize() {
    m_initialized = true;
    return true;
}

void NetProviderLOOP::Shutdown() {
    Disconnect();
    m_initialized = false;
}

bool NetProviderLOOP::Connect(const char* host, uint16_t port) {
    (void)host; (void)port;
    m_connected = true;
    return true;
}

void NetProviderLOOP::Disconnect() {
    m_connected = false;
    if (m_buffer) {
        free(m_buffer);
        m_buffer = nullptr;
    }
    m_bufferSize = 0;
}

bool NetProviderLOOP::IsConnected() const { return m_connected; }

bool NetProviderLOOP::Send(const void* data, uint32_t size) {
    if (!data || size == 0) return false;
    if (m_buffer) free(m_buffer);
    m_buffer = malloc(size);
    if (!m_buffer) return false;
    memcpy(m_buffer, data, size);
    m_bufferSize = size;
    return true;
}

bool NetProviderLOOP::Receive(void* buffer, uint32_t size, uint32_t* bytesRead) {
    if (!buffer || !m_buffer) {
        if (bytesRead) *bytesRead = 0;
        return false;
    }
    uint32_t copySize = (size < m_bufferSize) ? size : m_bufferSize;
    memcpy(buffer, m_buffer, copySize);
    if (bytesRead) *bytesRead = copySize;
    free(m_buffer);
    m_buffer = nullptr;
    m_bufferSize = 0;
    return true;
}
