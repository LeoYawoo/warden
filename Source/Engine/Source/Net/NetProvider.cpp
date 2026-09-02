#include "NetProvider.h"

// Reverse engineered from Warcraft III binary

NetProvider::NetProvider() : m_providerType(PROVIDER_UNKNOWN), m_initialized(false) {}
NetProvider::~NetProvider() { Shutdown(); }

bool NetProvider::Initialize() {
    m_initialized = true;
    return true;
}

void NetProvider::Shutdown() {
    m_initialized = false;
}

bool NetProvider::Connect(const char* host, uint16_t port) {
    (void)host; (void)port;
    return false;
}

void NetProvider::Disconnect() {}

bool NetProvider::IsConnected() const {
    return false;
}

bool NetProvider::Send(const void* data, uint32_t size) {
    (void)data; (void)size;
    return false;
}

bool NetProvider::Receive(void* buffer, uint32_t size, uint32_t* bytesRead) {
    (void)buffer; (void)size;
    if (bytesRead) *bytesRead = 0;
    return false;
}

const char* NetProvider::GetProviderName() const { return m_providerName.c_str(); }
int32_t NetProvider::GetProviderType() const { return m_providerType; }
