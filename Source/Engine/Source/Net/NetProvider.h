#pragma once

#include <cstdint>
#include <string>

// Forward declarations
class NetClient;

// Reverse engineered from Warcraft III binary
// NetProvider manages network providers

class NetProvider {
public:
    NetProvider();
    virtual ~NetProvider();

    // Provider operations
    virtual bool Initialize();
    virtual void Shutdown();

    // Connection operations
    virtual bool Connect(const char* host, uint16_t port);
    virtual void Disconnect();
    virtual bool IsConnected() const;

    // Data operations
    virtual bool Send(const void* data, uint32_t size);
    virtual bool Receive(void* buffer, uint32_t size, uint32_t* bytesRead = nullptr);

    // Provider properties
    const char* GetProviderName() const;
    int32_t GetProviderType() const;

    // Provider types
    enum Type {
        PROVIDER_UNKNOWN = 0,
        PROVIDER_BNET = 1,
        PROVIDER_LOOP = 2,
        PROVIDER_LTCP = 3
    };

protected:
    std::string m_providerName;
    int32_t m_providerType;
    bool m_initialized;
};
