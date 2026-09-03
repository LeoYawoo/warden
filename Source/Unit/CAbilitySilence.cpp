#include "CAbilitySilence.h"

// Reverse engineered from Warcraft III binary

CAbilitySilence::CAbilitySilence() : m_duration(0.0f), m_radius(0.0f), m_active(false) {}
CAbilitySilence::~CAbilitySilence() {}

float CAbilitySilence::GetDuration() const { return m_duration; }
void CAbilitySilence::SetDuration(float duration) { m_duration = duration; }

float CAbilitySilence::GetRadius() const { return m_radius; }
void CAbilitySilence::SetRadius(float radius) { m_radius = radius; }

bool CAbilitySilence::IsActive() const { return m_active; }
void CAbilitySilence::SetActive(bool active) { m_active = active; }
