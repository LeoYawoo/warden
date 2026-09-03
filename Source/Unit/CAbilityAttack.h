#pragma once

#include <cstdint>

// Forward declarations
class CUnit;

// Reverse engineered from Warcraft III binary
// CAbilityAttack manages attack abilities

class CAbilityAttack {
public:
    CAbilityAttack();
    ~CAbilityAttack();

    // Attack properties
    int32_t GetAttackDamage() const;
    void SetAttackDamage(int32_t damage);

    float GetAttackRange() const;
    void SetAttackRange(float range);

    float GetAttackCooldown() const;
    void SetAttackCooldown(float cooldown);

    int32_t GetAttackType() const;
    void SetAttackType(int32_t type);

    // Attack state
    bool IsAttacking() const;
    void SetAttacking(bool attacking);

    // Attack target
    CUnit* GetTarget() const;
    void SetTarget(CUnit* target);

protected:
    int32_t m_attackDamage;
    float m_attackRange;
    float m_attackCooldown;
    int32_t m_attackType;
    bool m_attacking;
    CUnit* m_target;
};
