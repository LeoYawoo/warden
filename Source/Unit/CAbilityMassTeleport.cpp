#include "CAbilityMassTeleport.h"

// Reverse engineered from Warcraft III binary

CAbilityMassTeleport::CAbilityMassTeleport()
    : m_radius(0.0f), m_castTime(0.0f), m_casting(false),
      m_targetX(0.0f), m_targetY(0.0f) {
}

CAbilityMassTeleport::~CAbilityMassTeleport() {}

float CAbilityMassTeleport::GetRadius() const { return m_radius; }
void CAbilityMassTeleport::SetRadius(float radius) { m_radius = radius; }

float CAbilityMassTeleport::GetCastTime() const { return m_castTime; }
void CAbilityMassTeleport::SetCastTime(float castTime) { m_castTime = castTime; }

bool CAbilityMassTeleport::IsCasting() const { return m_casting; }
void CAbilityMassTeleport::SetCasting(bool casting) { m_casting = casting; }

float CAbilityMassTeleport::GetTargetX() const { return m_targetX; }
float CAbilityMassTeleport::GetTargetY() const { return m_targetY; }

void CAbilityMassTeleport::SetTarget(float x, float y) {
    m_targetX = x;
    m_targetY = y;
}
