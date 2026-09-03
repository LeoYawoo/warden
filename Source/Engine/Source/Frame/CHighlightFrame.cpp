#include "CHighlightFrame.h"

// Reverse engineered from Warcraft III binary

CHighlightFrame::CHighlightFrame() : m_highlighted(false), m_highlightColor(0xFFFF0000) {}
CHighlightFrame::~CHighlightFrame() {}

bool CHighlightFrame::IsHighlighted() const { return m_highlighted; }
void CHighlightFrame::SetHighlighted(bool highlighted) { m_highlighted = highlighted; }

uint32_t CHighlightFrame::GetHighlightColor() const { return m_highlightColor; }
void CHighlightFrame::SetHighlightColor(uint32_t color) { m_highlightColor = color; }
