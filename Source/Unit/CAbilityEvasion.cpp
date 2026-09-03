#include "CAbilityEvasion.h"

// Reverse engineered from Warcraft III binary

CAbilityEvasion::CAbilityEvasion() : m_chance(0.0f), m_evading(false) {}
CAbilityEvasion::~CAbilityEvasion() {}

float CAbilityEvasion::GetChance() const { return m_chance; }
void CAbilityEvasion::SetChance(float chance) { m_chance = chance; }

bool CAbilityEvasion::IsEvading() const { return m_evading; }
void CAbilityEvasion::SetEvading(bool evading) { m_evading = evading; }
