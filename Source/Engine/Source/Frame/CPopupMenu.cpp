#include "CPopupMenu.h"

// Reverse engineered from Warcraft III binary

CPopupMenu::CPopupMenu() : m_popupX(0), m_popupY(0) { m_controlType = "PopupMenu"; }
CPopupMenu::~CPopupMenu() {}

float CPopupMenu::GetPopupX() const { return m_popupX; }
float CPopupMenu::GetPopupY() const { return m_popupY; }
void CPopupMenu::SetPopupPosition(float x, float y) { m_popupX = x; m_popupY = y; }

void CPopupMenu::Show(float x, float y) {
    m_popupX = x;
    m_popupY = y;
    SetOpen(true);
    SetVisible(true);
}

void CPopupMenu::Hide() {
    SetOpen(false);
    SetVisible(false);
}
