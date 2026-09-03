#include "CDestructable.h"

// Reverse engineered from Warcraft III binary

CDestructable::CDestructable()
    : m_destructableId(0), m_health(0), m_maxHealth(0),
      m_invulnerable(false), m_x(0.0f), m_y(0.0f) {
}

CDestructable::~CDestructable() {}

int32_t CDestructable::GetDestructableId() const { return m_destructableId; }
void CDestructable::SetDestructableId(int32_t id) { m_destructableId = id; }

const char* CDestructable::GetDestructableName() const { return m_destructableName.c_str(); }
void CDestructable::SetDestructableName(const char* name) { m_destructableName = name ? name : ""; }

int32_t CDestructable::GetHealth() const { return m_health; }
void CDestructable::SetHealth(int32_t health) { m_health = health; }

int32_t CDestructable::GetMaxHealth() const { return m_maxHealth; }
void CDestructable::SetMaxHealth(int32_t maxHealth) { m_maxHealth = maxHealth; }

bool CDestructable::IsInvulnerable() const { return m_invulnerable; }
void CDestructable::SetInvulnerable(bool invulnerable) { m_invulnerable = invulnerable; }

float CDestructable::GetX() const { return m_x; }
float CDestructable::GetY() const { return m_y; }

void CDestructable::SetPosition(float x, float y) {
    m_x = x;
    m_y = y;
}
