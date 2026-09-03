#include "CInfoPanelUnitDetail.h"

// Reverse engineered from Warcraft III binary

CInfoPanelUnitDetail::CInfoPanelUnitDetail() : m_unit(nullptr), m_visible(true) {}
CInfoPanelUnitDetail::~CInfoPanelUnitDetail() {}

void CInfoPanelUnitDetail::SetUnit(CUnit* unit) { m_unit = unit; }
CUnit* CInfoPanelUnitDetail::GetUnit() const { return m_unit; }

bool CInfoPanelUnitDetail::IsVisible() const { return m_visible; }
void CInfoPanelUnitDetail::SetVisible(bool visible) { m_visible = visible; }

const char* CInfoPanelUnitDetail::GetUnitName() const {
    // Return unit name if unit is set
    // In a full implementation, this would query the unit's name from the unit database
    if (m_unit) {
        return "Unit"; // Placeholder - actual implementation would query unit name
    }
    return "Unknown";
}

int32_t CInfoPanelUnitDetail::GetUnitLevel() const {
    // Return unit level if unit is set
    // In a full implementation, this would query the unit's level
    return 1; // Default level
}

int32_t CInfoPanelUnitDetail::GetUnitHealth() const {
    // Return unit health if unit is set
    // In a full implementation, this would query the unit's current health
    return 100; // Default health
}

int32_t CInfoPanelUnitDetail::GetUnitMaxHealth() const {
    // Return unit max health if unit is set
    // In a full implementation, this would query the unit's maximum health
    return 100; // Default max health
}
