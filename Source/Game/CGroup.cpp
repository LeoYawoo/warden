#include "CGroup.h"
#include <algorithm>

// Reverse engineered from Warcraft III binary

CGroup::CGroup() : m_groupId(0) {}
CGroup::~CGroup() { Clear(); }

int32_t CGroup::GetGroupId() const { return m_groupId; }
void CGroup::SetGroupId(int32_t id) { m_groupId = id; }

void CGroup::AddUnit(CUnit* unit) {
    if (unit && !ContainsUnit(unit)) {
        m_units.push_back(unit);
    }
}

void CGroup::RemoveUnit(CUnit* unit) {
    auto it = std::find(m_units.begin(), m_units.end(), unit);
    if (it != m_units.end()) {
        m_units.erase(it);
    }
}

void CGroup::Clear() {
    m_units.clear();
}

size_t CGroup::GetUnitCount() const { return m_units.size(); }

CUnit* CGroup::GetUnit(size_t index) const {
    if (index < m_units.size()) return m_units[index];
    return nullptr;
}

CUnit* CGroup::GetUnitById(int32_t unitId) const {
    // Find unit by ID
    // In a full implementation, this would iterate through units
    // and compare their IDs with the given unitId
    // For now, return nullptr as CUnit doesn't have GetId() method yet
    (void)unitId;
    return nullptr;
}

bool CGroup::ContainsUnit(CUnit* unit) const {
    return std::find(m_units.begin(), m_units.end(), unit) != m_units.end();
}
