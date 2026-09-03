#include "CCustomData.h"

// Reverse engineered from Warcraft III binary

CCustomData::CCustomData() {}
CCustomData::~CCustomData() {}

bool CCustomData::SetData(const char* key, const char* value) {
    if (!key || !value) return false;
    m_data[key] = value;
    return true;
}

bool CCustomData::GetData(const char* key, std::string& value) const {
    if (!key) return false;
    auto it = m_data.find(key);
    if (it != m_data.end()) {
        value = it->second;
        return true;
    }
    return false;
}

bool CCustomData::HasData(const char* key) const {
    if (!key) return false;
    return m_data.find(key) != m_data.end();
}

bool CCustomData::RemoveData(const char* key) {
    if (!key) return false;
    return m_data.erase(key) > 0;
}

size_t CCustomData::GetCount() const { return m_data.size(); }

void CCustomData::Clear() { m_data.clear(); }
