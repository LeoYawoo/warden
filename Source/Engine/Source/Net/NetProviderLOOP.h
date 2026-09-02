#pragma once

#include "NetProvider.h"

// Reverse engineered from Warcraft III binary
// NetProviderLOOP manages loopback network provider

class NetProviderLOOP : public NetProvider {
public:
    NetProviderLOOP();
    ~NetProviderLOOP() override;

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
    void* m_buffer;
    uint32_t m_bufferSize;
};
