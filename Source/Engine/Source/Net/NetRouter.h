#pragma once

#include <cstdint>
#include <string>
#include <vector>

// Forward declarations
class NetProvider;

// Reverse engineered from Warcraft III binary
// NetRouter manages network routing

class NetRouter {
public:
    NetRouter();
    ~NetRouter();

    // Router operations
    bool Initialize();
    void Shutdown();

    // Provider management
    void AddProvider(NetProvider* provider);
    void RemoveProvider(NetProvider* provider);
    size_t GetProviderCount() const;
    NetProvider* GetProvider(size_t index) const;

    // Routing operations
    bool Route(const void* data, uint32_t size, int32_t providerIndex = -1);

    // Router state
    bool IsInitialized() const;

protected:
    std::vector<NetProvider*> m_providers;
    bool m_initialized;
};
