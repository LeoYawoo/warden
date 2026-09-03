#include "CSimpleCheckbox.h"

// Reverse engineered from Warcraft III binary

CSimpleCheckbox::CSimpleCheckbox() : m_textColor(0xFFFFFFFF) {}
CSimpleCheckbox::~CSimpleCheckbox() {}

void CSimpleCheckbox::SetTextColor(uint32_t color) { m_textColor = color; }
uint32_t CSimpleCheckbox::GetTextColor() const { return m_textColor; }
