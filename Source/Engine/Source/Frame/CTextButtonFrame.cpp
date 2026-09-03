#include "CTextButtonFrame.h"

// Reverse engineered from Warcraft III binary

CTextButtonFrame::CTextButtonFrame() : m_textColor(0xFFFFFFFF), m_disabledColor(0xFF808080) {}
CTextButtonFrame::~CTextButtonFrame() {}

uint32_t CTextButtonFrame::GetTextColor() const { return m_textColor; }
void CTextButtonFrame::SetTextColor(uint32_t color) { m_textColor = color; }

uint32_t CTextButtonFrame::GetDisabledColor() const { return m_disabledColor; }
void CTextButtonFrame::SetDisabledColor(uint32_t color) { m_disabledColor = color; }
