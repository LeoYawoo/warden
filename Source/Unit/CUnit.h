#pragma once

#include "Engine/Source/Agile/CAgent.h"
#include "Engine/Source/Agile/AgentRefMini.h"
#include "Engine/Source/Agile/SmartPosition.h"
#include "Engine/Source/Agile/Float.h"

// Forward declarations
class CWidget;
class CAbility;

// Reverse engineered from Warcraft III binary
// Address: 0x88A8A4
// CUnit is the main unit class in Warcraft III

class CUnit : public CAgentBaseAbs {
public:
    CUnit();
    virtual ~CUnit();

    // Unit properties
    int32_t GetUnitId() const;
    int32_t GetLevel() const;
    bool DisplaysHP() const;
    bool DisplaysMana() const;
    bool IsHeroUnit() const;

    // Health/Mana
    int32_t BaseDefense() const;
    int32_t BaseMaxMana() const;
    float GetNormalizedMana() const;

    // Combat
    float AcquireRange() const;
    float CastBackSwing() const;
    int32_t RepulsePrio() const;
    int32_t RepulseParam() const;

    // Upgrades
    int32_t AttackUpgrade() const;
    int32_t DefenseUpgrade() const;
    int32_t GetsUpgrade(int32_t upgradeId) const;
    int32_t GetArmorUpgradeId() const;
    int32_t GetMeleeUpgradeId() const;
    int32_t GetRangedUpgradeId() const;
    int32_t GetCasterUpgradeId() const;

    // State
    void ClearIsDead();
    void SetRaiseable(int32_t raiseable);
    void SetNeedsElevPos(int32_t needsElev);
    void SetOffsetVisual(int32_t offset);
    void SetScaleBullets(int32_t scale);
    void SetImpairedVision(int32_t impaired);
    void SetReturnGold(int32_t gold);
    void SetReturnLumber(int32_t lumber);
    void ResetShadow(uint32_t shadowId);

    // Tasks
    void TaskCompleted();

    // Listeners
    void LifeListen(int32_t value, const float& delta, int32_t agentId, CAgent* agent, int shareType);
    void ManaListen(int32_t value, const float& delta, int32_t agentId, CAgent* agent, int shareType);

protected:
    // Unit data (offset +84 to +360)
    int32_t m_ownerId;          // offset +84
    int32_t m_unitId;           // offset +88
    int32_t m_typeId;           // offset +92
    int32_t m_flags;            // offset +96
    int32_t m_status;           // offset +100

    // Timers
    CAgentTimer m_attackTimer;  // offset +104
    CAgentTimer m_deathTimer;   // offset +124

    // Properties
    Float m_life;               // offset +152
    int32_t m_maxLife;          // offset +168
    Float m_mana;               // offset +172
    int32_t m_maxMana;          // offset +180
    Float m_armor;              // offset +184
    Float m_speed;              // offset +200
    Float m_turnRate;           // offset +208
    int32_t m_sightRange;       // offset +216
    Float m_acquireRange;       // offset +220
    int32_t m_level;            // offset +228
    int32_t m_experience;       // offset +232
    int32_t m_strength;         // offset +236

    // References
    AgentRefMini m_targetRef;   // offset +240
    Float m_damage;             // offset +252
    int32_t m_damageType;       // offset +268
    int32_t m_attackType;       // offset +272
    Float m_attackRange;        // offset +280
    int32_t m_attackCooldown;   // offset +296
    int32_t m_projectileSpeed;  // offset +300

    AgentRefMini m_ownerRef;    // offset +304
    AgentRefMini m_leaderRef;   // offset +316

    // Position
    SmartPosition m_position;   // offset +356
};
