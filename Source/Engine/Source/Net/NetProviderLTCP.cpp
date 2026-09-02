#include "NetProviderLTCP.h"

// Reverse engineered from Warcraft III binary

NetProviderLTCP::NetProviderLTCP() : m_connected(false), m_socket(nullptr) {
    m_providerType = PROVIDER_LTCP;
    m_providerName = "LAN TCP";
}

NetProviderLTCP::~NetProviderLTCP() { Shutdown(); }

bool NetProviderLTCP::Initialize() {
    m_initialized = true;
    return true;
}

void NetProviderLTCP::Shutdown() {
    Disconnect();
    m_initialized = false;
}

bool NetProviderLTCP::Connect(const char* host, uint16_t port) {
    (void)host; (void)port;
    m_connected = true;
    return true;
}

void NetProviderLTCP::Disconnect() {
    m_connected = false;
    m_socket = nullptr;
}

bool NetProviderLTCP::IsConnected() const { return m_connected; }

bool NetProviderLTCP::Send(const void* data, uint32_t size) {
    (void)data; (void)size;
    return m_connected;
}

bool NetProviderLTCP::Receive(void* buffer, uint32_t size, uint32_t* bytesRead) {
    (void)buffer; (void)size;
    if (bytesRead) *bytesRead = 0;
    return m_connected;
}
