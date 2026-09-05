#include "CRealmList.h"
#include <algorithm>

// Reverse engineered from Warcraft III binary

TSGrowableArray<RealmCategory*> CRealmList::s_categories;
int32_t CRealmList::s_selectedCategory = -1;
int32_t CRealmList::s_preferredCategory = -1;

CRealmList::CRealmList()
    : m_initialized(false), m_visible(false), m_selectedRealmIndex(-1) {
}

CRealmList::~CRealmList() { Shutdown(); }

bool CRealmList::Initialize() {
    m_initialized = true;
    return true;
}

void CRealmList::Shutdown() {
    m_initialized = false;
    m_realms.clear();
}

bool CRealmList::IsInitialized() const { return m_initialized; }

void CRealmList::AddRealm(const char* name, const char* address, int32_t port) {
    if (!name || !address) return;
    Realm realm;
    realm.name = name;
    realm.address = address;
    realm.port = port;
    m_realms.push_back(realm);
}

void CRealmList::RemoveRealm(const char* name) {
    if (!name) return;
    m_realms.erase(
        std::remove_if(m_realms.begin(), m_realms.end(),
            [name](const Realm& r) { return r.name == name; }),
        m_realms.end());
}

void CRealmList::ClearRealms() { m_realms.clear(); }

size_t CRealmList::GetRealmCount() const { return m_realms.size(); }

const char* CRealmList::GetRealmName(size_t index) const {
    return (index < m_realms.size()) ? m_realms[index].name.c_str() : nullptr;
}

const char* CRealmList::GetRealmAddress(size_t index) const {
    return (index < m_realms.size()) ? m_realms[index].address.c_str() : nullptr;
}

int32_t CRealmList::GetRealmPort(size_t index) const {
    return (index < m_realms.size()) ? m_realms[index].port : 0;
}

int32_t CRealmList::GetSelectedRealmIndex() const { return m_selectedRealmIndex; }
void CRealmList::SetSelectedRealmIndex(int32_t index) { m_selectedRealmIndex = index; }

bool CRealmList::IsVisible() const { return m_visible; }
void CRealmList::SetVisible(bool visible) { m_visible = visible; }

int32_t CRealmList::Sub4DE910(int32_t categoryIndex) {
    // IDA reverse-engineered function
    // Maps a user-facing category index to internal index
    if (categoryIndex < 0 || categoryIndex >= static_cast<int32_t>(s_categories.Count())) {
        return 0;
    }
    return categoryIndex;
}

void CRealmList::SetPreferredInfo(uint32_t index, int32_t pvp, int32_t rp) {
    // TODO: Implement preferred realm info setting
}
