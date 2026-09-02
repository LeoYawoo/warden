#pragma once

#include "NetProvider.h"

// Reverse engineered from Warcraft III binary
// NetProviderLTCP manages LAN TCP network provider

class NetProviderLTCP : public NetProvider {
public:
    NetProviderLTCP();
    ~NetProviderLTCP() override;

    // Provider operations
    bool Initialize() override;
    void Shutdown() override;

    // Connection operations
    bool Connect(const char* host, uint16_t port) override;
    void Disconnect() override;
    bool IsConnected() const override;

    // Data operations
    bool Send(const void* data, uint32_t size) override;
    bool Receive(void* buffer, uint32_t size, uint32_t* bytesRead = nullptr) override;

protected:
    bool m_connected;
    void* m_socket;
};
