#include "CProgressIndicator.h"
#include <algorithm>

// Reverse engineered from Warcraft III binary

CProgressIndicator::CProgressIndicator() : m_progress(0.0f), m_visible(true), m_animating(false) {}
CProgressIndicator::~CProgressIndicator() {}

float CProgressIndicator::GetProgress() const { return m_progress; }
void CProgressIndicator::SetProgress(float progress) { m_progress = std::max(0.0f, std::min(progress, 1.0f)); }

bool CProgressIndicator::IsVisible() const { return m_visible; }
void CProgressIndicator::SetVisible(bool visible) { m_visible = visible; }

bool CProgressIndicator::IsAnimating() const { return m_animating; }
void CProgressIndicator::SetAnimating(bool animating) { m_animating = animating; }
