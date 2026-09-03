#include "CAbilityCouple.h"

// Reverse engineered from Warcraft III binary

CAbilityCouple::CAbilityCouple() : m_partner(nullptr), m_distance(0.0f), m_coupled(false) {}
CAbilityCouple::~CAbilityCouple() {}

CUnit* CAbilityCouple::GetPartner() const { return m_partner; }
void CAbilityCouple::SetPartner(CUnit* partner) { m_partner = partner; }

float CAbilityCouple::GetDistance() const { return m_distance; }
void CAbilityCouple::SetDistance(float distance) { m_distance = distance; }

bool CAbilityCouple::IsCoupled() const { return m_coupled; }
void CAbilityCouple::SetCoupled(bool coupled) { m_coupled = coupled; }
