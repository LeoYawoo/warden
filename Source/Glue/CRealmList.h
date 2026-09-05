#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include "Common/TSGrowableArray.h"

// Reverse engineered from Warcraft III binary
// CRealmList manages the realm list

struct RealmEntry {
    char name[64];
    char address[64];
    int32_t port;
};

struct RealmCategory {
    TSGrowableArray<int32_t> m_realms;
    uint32_t uint14 = 0;
};

class CRealmList {
public:
    CRealmList();
    ~CRealmList();

    // IDA reverse-engineered names
    static TSGrowableArray<RealmCategory*> s_categories;
    static int32_t s_selectedCategory;
    static int32_t s_preferredCategory;
    static int32_t Sub4DE910(int32_t categoryIndex);
    static void SetPreferredInfo(uint32_t index, int32_t pvp, int32_t rp);

    // Realm operations
    bool Initialize();
    void Shutdown();
    bool IsInitialized() const;

    // Realm management
    void AddRealm(const char* name, const char* address, int32_t port);
    void RemoveRealm(const char* name);
    void ClearRealms();

    // Realm queries
    size_t GetRealmCount() const;
    const char* GetRealmName(size_t index) const;
    const char* GetRealmAddress(size_t index) const;
    int32_t GetRealmPort(size_t index) const;

    // Realm selection
    int32_t GetSelectedRealmIndex() const;
    void SetSelectedRealmIndex(int32_t index);

    // Realm state
    bool IsVisible() const;
    void SetVisible(bool visible);

protected:
    struct Realm {
        std::string name;
        std::string address;
        int32_t port;
    };

    bool m_initialized;
    bool m_visible;
    int32_t m_selectedRealmIndex;
    std::vector<Realm> m_realms;
};
