#include "CSimpleStatusBar.h"
#include <algorithm>

// Reverse engineered from Warcraft III binary

CSimpleStatusBar::CSimpleStatusBar() : m_progress(0.0f), m_barColor(0xFF00FF00), m_backgroundColor(0xFF333333) {}
CSimpleStatusBar::~CSimpleStatusBar() {}

float CSimpleStatusBar::GetProgress() const { return m_progress; }
void CSimpleStatusBar::SetProgress(float progress) { m_progress = std::max(0.0f, std::min(progress, 1.0f)); }

uint32_t CSimpleStatusBar::GetBarColor() const { return m_barColor; }
void CSimpleStatusBar::SetBarColor(uint32_t color) { m_barColor = color; }

uint32_t CSimpleStatusBar::GetBackgroundColor() const { return m_backgroundColor; }
void CSimpleStatusBar::SetBackgroundColor(uint32_t color) { m_backgroundColor = color; }
