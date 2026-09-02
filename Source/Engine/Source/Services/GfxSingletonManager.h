#pragma once

#include <cstdint>
#include <unordered_map>
#include <string>

// Reverse engineered from Warcraft III binary
// GfxSingletonManager manages graphics singletons

class GfxSingletonManager {
public:
    GfxSingletonManager();
    ~GfxSingletonManager();

    // Singleton operations
    void* GetSingleton(const char* name) const;
    void SetSingleton(const char* name, void* singleton);
    void RemoveSingleton(const char* name);

    // Manager operations
    void Clear();
    size_t GetCount() const;

    // Static access
    static GfxSingletonManager& GetInstance();

private:
    std::unordered_map<std::string, void*> m_singletons;
};
