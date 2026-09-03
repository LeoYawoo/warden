#include "CInfoBar.h"

// Reverse engineered from Warcraft III binary

CInfoBar::CInfoBar() : m_visible(true) {}
CInfoBar::~CInfoBar() {}

const char* CInfoBar::GetInfoText() const { return m_infoText.c_str(); }
void CInfoBar::SetInfoText(const char* text) { m_infoText = text ? text : ""; }

bool CInfoBar::IsVisible() const { return m_visible; }
void CInfoBar::SetVisible(bool visible) { m_visible = visible; }
