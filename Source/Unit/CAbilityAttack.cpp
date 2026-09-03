#include "CAbilityAttack.h"

// Reverse engineered from Warcraft III binary

CAbilityAttack::CAbilityAttack()
    : m_attackDamage(0), m_attackRange(0.0f), m_attackCooldown(0.0f),
      m_attackType(0), m_attacking(false), m_target(nullptr) {
}

CAbilityAttack::~CAbilityAttack() {}

int32_t CAbilityAttack::GetAttackDamage() const { return m_attackDamage; }
void CAbilityAttack::SetAttackDamage(int32_t damage) { m_attackDamage = damage; }

float CAbilityAttack::GetAttackRange() const { return m_attackRange; }
void CAbilityAttack::SetAttackRange(float range) { m_attackRange = range; }

float CAbilityAttack::GetAttackCooldown() const { return m_attackCooldown; }
void CAbilityAttack::SetAttackCooldown(float cooldown) { m_attackCooldown = cooldown; }

int32_t CAbilityAttack::GetAttackType() const { return m_attackType; }
void CAbilityAttack::SetAttackType(int32_t type) { m_attackType = type; }

bool CAbilityAttack::IsAttacking() const { return m_attacking; }
void CAbilityAttack::SetAttacking(bool attacking) { m_attacking = attacking; }

CUnit* CAbilityAttack::GetTarget() const { return m_target; }
void CAbilityAttack::SetTarget(CUnit* target) { m_target = target; }
