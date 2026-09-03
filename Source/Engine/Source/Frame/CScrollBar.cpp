#include "CScrollBar.h"
#include <algorithm>

// Reverse engineered from Warcraft III binary

CScrollBar::CScrollBar() : m_scrollPosition(0), m_scrollRange(100), m_pageSize(10), m_vertical(true) {
    m_controlType = "ScrollBar";
}

CScrollBar::~CScrollBar() {}

float CScrollBar::GetScrollPosition() const { return m_scrollPosition; }
void CScrollBar::SetScrollPosition(float position) { m_scrollPosition = std::max(0.0f, std::min(position, m_scrollRange)); }

float CScrollBar::GetScrollRange() const { return m_scrollRange; }
void CScrollBar::SetScrollRange(float range) { m_scrollRange = range; }

float CScrollBar::GetPageSize() const { return m_pageSize; }
void CScrollBar::SetPageSize(float pageSize) { m_pageSize = pageSize; }

void CScrollBar::ScrollUp(float amount) { m_scrollPosition = std::max(0.0f, m_scrollPosition - amount); }
void CScrollBar::ScrollDown(float amount) { m_scrollPosition = std::min(m_scrollRange, m_scrollPosition + amount); }

bool CScrollBar::IsVertical() const { return m_vertical; }
void CScrollBar::SetVertical(bool vertical) { m_vertical = vertical; }
