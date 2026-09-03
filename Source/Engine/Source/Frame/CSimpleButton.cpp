#include "CSimpleButton.h"

// Reverse engineered from Warcraft III binary

CSimpleButton::CSimpleButton() : m_textColor(0xFFFFFFFF), m_font(nullptr), m_disabled(false) {}
CSimpleButton::~CSimpleButton() {}

void CSimpleButton::SetTextColor(uint32_t color) { m_textColor = color; }
uint32_t CSimpleButton::GetTextColor() const { return m_textColor; }

void CSimpleButton::SetFont(CGxuFont* font) { m_font = font; }
CGxuFont* CSimpleButton::GetFont() const { return m_font; }

bool CSimpleButton::IsDisabled() const { return m_disabled; }
void CSimpleButton::SetDisabled(bool disabled) { m_disabled = disabled; }
