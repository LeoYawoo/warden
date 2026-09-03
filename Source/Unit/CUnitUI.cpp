#include "CUnitUI.h"

// Reverse engineered from Warcraft III binary

CUnitUI::CUnitUI()
    : m_unit(nullptr), m_selected(false), m_highlighted(false), m_visible(true) {
}

CUnitUI::~CUnitUI() {}

void CUnitUI::SetUnit(CUnit* unit) { m_unit = unit; }
CUnit* CUnitUI::GetUnit() const { return m_unit; }

bool CUnitUI::IsSelected() const { return m_selected; }
void CUnitUI::SetSelected(bool selected) { m_selected = selected; }

bool CUnitUI::IsHighlighted() const { return m_highlighted; }
void CUnitUI::SetHighlighted(bool highlighted) { m_highlighted = highlighted; }

bool CUnitUI::IsVisible() const { return m_visible; }
void CUnitUI::SetVisible(bool visible) { m_visible = visible; }
