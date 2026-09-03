#include "CCommandBar.h"

// Reverse engineered from Warcraft III binary

CCommandBar::CCommandBar() : m_selectedUnit(nullptr), m_visible(true) {}
CCommandBar::~CCommandBar() {}

void CCommandBar::SetSelectedUnit(CUnit* unit) { m_selectedUnit = unit; }
CUnit* CCommandBar::GetSelectedUnit() const { return m_selectedUnit; }

bool CCommandBar::IsVisible() const { return m_visible; }
void CCommandBar::SetVisible(bool visible) { m_visible = visible; }

size_t CCommandBar::GetCommandCount() const {
    // TODO: Implement command count based on unit
    return 0;
}

const char* CCommandBar::GetCommandName(size_t index) const {
    (void)index;
    // TODO: Implement command name lookup
    return nullptr;
}

int32_t CCommandBar::GetCommandId(size_t index) const {
    (void)index;
    // TODO: Implement command ID lookup
    return 0;
}
