#include "CPortraitButton.h"

// Reverse engineered from Warcraft III binary

CPortraitButton::CPortraitButton() : m_unit(nullptr), m_visible(true), m_playing(false) {}
CPortraitButton::~CPortraitButton() {}

void CPortraitButton::SetUnit(CUnit* unit) { m_unit = unit; }
CUnit* CPortraitButton::GetUnit() const { return m_unit; }

bool CPortraitButton::IsVisible() const { return m_visible; }
void CPortraitButton::SetVisible(bool visible) { m_visible = visible; }

bool CPortraitButton::IsPlaying() const { return m_playing; }
void CPortraitButton::SetPlaying(bool playing) { m_playing = playing; }
