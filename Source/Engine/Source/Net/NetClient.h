#pragma once

#include <cstdint>
#include <string>

// Forward declarations
class CDataStore;

// Reverse engineered from Warcraft III binary
// NetClient manages network client connections

class NetClient {
public:
    NetClient();
    ~NetClient();

    // Client operations
    bool Connect(const char* host, uint16_t port);
    void Disconnect();
    bool IsConnected() const;

    // Data operations
    bool Send(const void* data, uint32_t size);
    bool Receive(void* buffer, uint32_t size, uint32_t* bytesRead = nullptr);

    // Client properties
    const char* GetHost() const;
    uint16_t GetPort() const;
    int32_t GetState() const;

    // Client state
    enum State {
        DISCONNECTED = 0,
        CONNECTING = 1,
        CONNECTED = 2,
        ERROR = 3
    };

protected:
    std::string m_host;
    uint16_t m_port;
    int32_t m_state;
    void* m_socket;
};
