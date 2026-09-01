#include "CAbility.h"

// Reverse engineered from Warcraft III binary
// Address: 0x787784

CAbility::CAbility()
    : m_abilityId(0),
      m_abilityType(0),
      m_level(0),
      m_maxLevel(0),
      m_cooldown(0.0f),
      m_cooldownLeft(0.0f),
      m_active(false),
      m_flags(0),
      m_ownerId(0),
      m_timer() {
    // Virtual table set in constructor
}

CAbility::~CAbility() {
    // Virtual destructor
}

void CAbility::Activate() {
    m_active = true;
}

void CAbility::Deactivate() {
    m_active = false;
}

bool CAbility::IsActive() const {
    return m_active;
}

int CAbility::GetLevel() const {
    return m_level;
}

void CAbility::SetLevel(int level) {
    if (level >= 0 && level <= m_maxLevel) {
        m_level = level;
    }
}

float CAbility::GetCooldown() const {
    return m_cooldown;
}

void CAbility::SetCooldown(float cooldown) {
    m_cooldown = cooldown;
    m_cooldownLeft = cooldown;
}

bool CAbility::IsOnCooldown() const {
    return m_cooldownLeft > 0.0f;
}

void CAbility::UpdateCooldown(float deltaTime) {
    if (m_cooldownLeft > 0.0f) {
        m_cooldownLeft -= deltaTime;
        if (m_cooldownLeft < 0.0f) {
            m_cooldownLeft = 0.0f;
        }
    }
}
