#include "NetClient.h"

// Reverse engineered from Warcraft III binary

NetClient::NetClient() : m_port(0), m_state(DISCONNECTED), m_socket(nullptr) {}
NetClient::~NetClient() { Disconnect(); }

bool NetClient::Connect(const char* host, uint16_t port) {
    if (!host) return false;
    m_host = host;
    m_port = port;
    m_state = CONNECTING;
    // TODO: Implement actual connection
    m_state = CONNECTED;
    return true;
}

void NetClient::Disconnect() {
    m_state = DISCONNECTED;
    m_socket = nullptr;
}

bool NetClient::IsConnected() const {
    return m_state == CONNECTED;
}

bool NetClient::Send(const void* data, uint32_t size) {
    (void)data; (void)size;
    return IsConnected();
}

bool NetClient::Receive(void* buffer, uint32_t size, uint32_t* bytesRead) {
    (void)buffer; (void)size;
    if (bytesRead) *bytesRead = 0;
    return IsConnected();
}

const char* NetClient::GetHost() const { return m_host.c_str(); }
uint16_t NetClient::GetPort() const { return m_port; }
int32_t NetClient::GetState() const { return m_state; }
