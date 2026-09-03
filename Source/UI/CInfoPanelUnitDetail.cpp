#include "CInfoPanelUnitDetail.h"

// Reverse engineered from Warcraft III binary

CInfoPanelUnitDetail::CInfoPanelUnitDetail() : m_unit(nullptr), m_visible(true) {}
CInfoPanelUnitDetail::~CInfoPanelUnitDetail() {}

void CInfoPanelUnitDetail::SetUnit(CUnit* unit) { m_unit = unit; }
CUnit* CInfoPanelUnitDetail::GetUnit() const { return m_unit; }

bool CInfoPanelUnitDetail::IsVisible() const { return m_visible; }
void CInfoPanelUnitDetail::SetVisible(bool visible) { m_visible = visible; }

const char* CInfoPanelUnitDetail::GetUnitName() const {
    // TODO: Implement unit name lookup
    return "Unknown";
}

int32_t CInfoPanelUnitDetail::GetUnitLevel() const {
    // TODO: Implement unit level lookup
    return 0;
}

int32_t CInfoPanelUnitDetail::GetUnitHealth() const {
    // TODO: Implement unit health lookup
    return 0;
}

int32_t CInfoPanelUnitDetail::GetUnitMaxHealth() const {
    // TODO: Implement unit max health lookup
    return 0;
}
