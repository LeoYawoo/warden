#include "CSelectionWar3.h"
#include <algorithm>

// Reverse engineered from Warcraft III binary

CSelectionWar3::CSelectionWar3() : m_multiSelect(true) {}
CSelectionWar3::~CSelectionWar3() { ClearSelection(); }

void CSelectionWar3::SelectUnit(CUnit* unit) {
    if (unit && !IsUnitSelected(unit)) {
        m_selectedUnits.push_back(unit);
    }
}

void CSelectionWar3::DeselectUnit(CUnit* unit) {
    auto it = std::find(m_selectedUnits.begin(), m_selectedUnits.end(), unit);
    if (it != m_selectedUnits.end()) {
        m_selectedUnits.erase(it);
    }
}

void CSelectionWar3::ClearSelection() {
    m_selectedUnits.clear();
}

void CSelectionWar3::SelectAll() {
    // Select all units - implementation requires access to world unit list
    // For now, this is a placeholder for future implementation
    // In a full implementation, this would iterate through all units in the world
    // and add them to m_selectedUnits
}

size_t CSelectionWar3::GetSelectionCount() const { return m_selectedUnits.size(); }

CUnit* CSelectionWar3::GetSelectedUnit(size_t index) const {
    if (index < m_selectedUnits.size()) return m_selectedUnits[index];
    return nullptr;
}

bool CSelectionWar3::IsUnitSelected(CUnit* unit) const {
    return std::find(m_selectedUnits.begin(), m_selectedUnits.end(), unit) != m_selectedUnits.end();
}

bool CSelectionWar3::IsMultiSelect() const { return m_multiSelect; }
void CSelectionWar3::SetMultiSelect(bool multiSelect) { m_multiSelect = multiSelect; }
