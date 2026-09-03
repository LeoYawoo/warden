#include "CUnitDatabase.h"

// Reverse engineered from Warcraft III binary

CUnitDatabase::CUnitDatabase() : m_initialized(false) {}
CUnitDatabase::~CUnitDatabase() { Shutdown(); }

bool CUnitDatabase::Initialize() {
    m_initialized = true;
    return true;
}

void CUnitDatabase::Shutdown() {
    m_initialized = false;
    m_unitTypes.clear();
}

bool CUnitDatabase::IsInitialized() const { return m_initialized; }

bool CUnitDatabase::RegisterUnitType(int32_t typeId, const char* typeName) {
    if (!typeName) return false;
    m_unitTypes[typeId] = typeName;
    return true;
}

bool CUnitDatabase::UnregisterUnitType(int32_t typeId) {
    return m_unitTypes.erase(typeId) > 0;
}

bool CUnitDatabase::HasUnitType(int32_t typeId) const {
    return m_unitTypes.find(typeId) != m_unitTypes.end();
}

const char* CUnitDatabase::GetUnitTypeName(int32_t typeId) const {
    auto it = m_unitTypes.find(typeId);
    return (it != m_unitTypes.end()) ? it->second.c_str() : nullptr;
}

int32_t CUnitDatabase::GetUnitTypeCount() const {
    return static_cast<int32_t>(m_unitTypes.size());
}
