#include "CSimpleMessageFrame.h"

// Reverse engineered from Warcraft III binary

CSimpleMessageFrame::CSimpleMessageFrame() : m_textColor(0xFFFFFFFF) {}
CSimpleMessageFrame::~CSimpleMessageFrame() {}

void CSimpleMessageFrame::SetTextColor(uint32_t color) { m_textColor = color; }
uint32_t CSimpleMessageFrame::GetTextColor() const { return m_textColor; }
