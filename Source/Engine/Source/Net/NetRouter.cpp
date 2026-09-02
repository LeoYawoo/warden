#include "NetRouter.h"
#include "NetProvider.h"
#include <algorithm>

// Reverse engineered from Warcraft III binary

NetRouter::NetRouter() : m_initialized(false) {}
NetRouter::~NetRouter() { Shutdown(); }

bool NetRouter::Initialize() {
    m_initialized = true;
    return true;
}

void NetRouter::Shutdown() {
    m_providers.clear();
    m_initialized = false;
}

void NetRouter::AddProvider(NetProvider* provider) {
    if (provider) {
        m_providers.push_back(provider);
    }
}

void NetRouter::RemoveProvider(NetProvider* provider) {
    auto it = std::find(m_providers.begin(), m_providers.end(), provider);
    if (it != m_providers.end()) {
        m_providers.erase(it);
    }
}

size_t NetRouter::GetProviderCount() const {
    return m_providers.size();
}

NetProvider* NetRouter::GetProvider(size_t index) const {
    if (index < m_providers.size()) {
        return m_providers[index];
    }
    return nullptr;
}

bool NetRouter::Route(const void* data, uint32_t size, int32_t providerIndex) {
    if (!data || size == 0) return false;

    if (providerIndex >= 0 && static_cast<size_t>(providerIndex) < m_providers.size()) {
        return m_providers[providerIndex]->Send(data, size);
    }

    // Route to all connected providers
    bool sent = false;
    for (auto* provider : m_providers) {
        if (provider && provider->IsConnected()) {
            if (provider->Send(data, size)) {
                sent = true;
            }
        }
    }

    return sent;
}

bool NetRouter::IsInitialized() const {
    return m_initialized;
}
