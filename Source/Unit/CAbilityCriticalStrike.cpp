#include "CAbilityCriticalStrike.h"

// Reverse engineered from Warcraft III binary

CAbilityCriticalStrike::CAbilityCriticalStrike()
    : m_chance(0.0f), m_multiplier(1.0f), m_critical(false) {
}

CAbilityCriticalStrike::~CAbilityCriticalStrike() {}

float CAbilityCriticalStrike::GetChance() const { return m_chance; }
void CAbilityCriticalStrike::SetChance(float chance) { m_chance = chance; }

float CAbilityCriticalStrike::GetMultiplier() const { return m_multiplier; }
void CAbilityCriticalStrike::SetMultiplier(float multiplier) { m_multiplier = multiplier; }

bool CAbilityCriticalStrike::IsCritical() const { return m_critical; }
void CAbilityCriticalStrike::SetCritical(bool critical) { m_critical = critical; }
