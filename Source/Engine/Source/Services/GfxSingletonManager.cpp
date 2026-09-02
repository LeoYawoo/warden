#include "GfxSingletonManager.h"

// Reverse engineered from Warcraft III binary

GfxSingletonManager::GfxSingletonManager() {}
GfxSingletonManager::~GfxSingletonManager() { Clear(); }

void* GfxSingletonManager::GetSingleton(const char* name) const {
    if (!name) return nullptr;
    auto it = m_singletons.find(name);
    return it != m_singletons.end() ? it->second : nullptr;
}

void GfxSingletonManager::SetSingleton(const char* name, void* singleton) {
    if (name) m_singletons[name] = singleton;
}

void GfxSingletonManager::RemoveSingleton(const char* name) {
    if (name) m_singletons.erase(name);
}

void GfxSingletonManager::Clear() {
    m_singletons.clear();
}

size_t GfxSingletonManager::GetCount() const {
    return m_singletons.size();
}

GfxSingletonManager& GfxSingletonManager::GetInstance() {
    static GfxSingletonManager instance;
    return instance;
}
