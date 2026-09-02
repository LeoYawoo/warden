#include "NetProviderBNET.h"

// Reverse engineered from Warcraft III binary

NetProviderBNET::NetProviderBNET() : m_connected(false), m_socket(nullptr) {
    m_providerType = PROVIDER_BNET;
    m_providerName = "Battle.net";
}

NetProviderBNET::~NetProviderBNET() { Shutdown(); }

bool NetProviderBNET::Initialize() {
    m_initialized = true;
    return true;
}

void NetProviderBNET::Shutdown() {
    Disconnect();
    m_initialized = false;
}

bool NetProviderBNET::Connect(const char* host, uint16_t port) {
    (void)host; (void)port;
    m_connected = true;
    return true;
}

void NetProviderBNET::Disconnect() {
    m_connected = false;
    m_socket = nullptr;
}

bool NetProviderBNET::IsConnected() const { return m_connected; }

bool NetProviderBNET::Send(const void* data, uint32_t size) {
    (void)data; (void)size;
    return m_connected;
}

bool NetProviderBNET::Receive(void* buffer, uint32_t size, uint32_t* bytesRead) {
    (void)buffer; (void)size;
    if (bytesRead) *bytesRead = 0;
    return m_connected;
}
