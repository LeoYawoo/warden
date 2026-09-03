#include "CCommandBar.h"

// Reverse engineered from Warcraft III binary

CCommandBar::CCommandBar() : m_selectedUnit(nullptr), m_visible(true) {}
CCommandBar::~CCommandBar() {}

void CCommandBar::SetSelectedUnit(CUnit* unit) { m_selectedUnit = unit; }
CUnit* CCommandBar::GetSelectedUnit() const { return m_selectedUnit; }

bool CCommandBar::IsVisible() const { return m_visible; }
void CCommandBar::SetVisible(bool visible) { m_visible = visible; }

size_t CCommandBar::GetCommandCount() const {
    // Return default command count based on unit type
    // In a full implementation, this would query the unit's available commands
    if (m_selectedUnit) {
        return 4; // Default: Attack, Move, Stop, Hold Position
    }
    return 0;
}

const char* CCommandBar::GetCommandName(size_t index) const {
    // Return command name based on index
    static const char* defaultCommands[] = {"Attack", "Move", "Stop", "Hold Position"};
    if (index < 4) {
        return defaultCommands[index];
    }
    return nullptr;
}

int32_t CCommandBar::GetCommandId(size_t index) const {
    // Return command ID based on index
    static const int32_t defaultCommandIds[] = {851971, 851970, 851973, 851972};
    if (index < 4) {
        return defaultCommandIds[index];
    }
    return 0;
}
