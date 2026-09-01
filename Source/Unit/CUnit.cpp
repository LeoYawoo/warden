#include "CUnit.h"

// Reverse engineered from Warcraft III binary
// Address: 0x88A8A4

CUnit::CUnit()
    : CAgentBaseAbs(),
      m_ownerId(0),
      m_unitId(0),
      m_typeId(0),
      m_flags(0),
      m_status(0),
      m_attackTimer(),
      m_deathTimer(),
      m_life(0.0f),
      m_maxLife(0),
      m_mana(0.0f),
      m_maxMana(0),
      m_armor(0.0f),
      m_speed(0.0f),
      m_turnRate(0.0f),
      m_sightRange(0),
      m_acquireRange(0.0f),
      m_level(0),
      m_experience(0),
      m_strength(0),
      m_targetRef(),
      m_damage(0.0f),
      m_damageType(0),
      m_attackType(0),
      m_attackRange(0.0f),
      m_attackCooldown(0),
      m_projectileSpeed(0),
      m_ownerRef(),
      m_leaderRef(),
      m_position() {
    // Virtual table set in constructor
}

CUnit::~CUnit() {
    // Virtual destructor
}

int32_t CUnit::GetUnitId() const {
    return m_unitId;
}

int32_t CUnit::GetLevel() const {
    return m_level;
}

bool CUnit::DisplaysHP() const {
    return true;
}

bool CUnit::DisplaysMana() const {
    return m_maxMana > 0;
}

bool CUnit::IsHeroUnit() const {
    return (m_flags & 0x10) != 0;
}

int32_t CUnit::BaseDefense() const {
    return static_cast<int32_t>(m_armor.GetValue());
}

int32_t CUnit::BaseMaxMana() const {
    return m_maxMana;
}

float CUnit::GetNormalizedMana() const {
    if (m_maxMana > 0) {
        return m_mana.GetValue() / static_cast<float>(m_maxMana);
    }
    return 0.0f;
}

float CUnit::AcquireRange() const {
    return m_acquireRange.GetValue();
}

float CUnit::CastBackSwing() const {
    return 0.0f;
}

int32_t CUnit::RepulsePrio() const {
    return 0;
}

int32_t CUnit::RepulseParam() const {
    return 0;
}

int32_t CUnit::AttackUpgrade() const {
    return 0;
}

int32_t CUnit::DefenseUpgrade() const {
    return 0;
}

int32_t CUnit::GetsUpgrade(int32_t upgradeId) const {
    (void)upgradeId;
    return 0;
}

int32_t CUnit::GetArmorUpgradeId() const {
    return 0;
}

int32_t CUnit::GetMeleeUpgradeId() const {
    return 0;
}

int32_t CUnit::GetRangedUpgradeId() const {
    return 0;
}

int32_t CUnit::GetCasterUpgradeId() const {
    return 0;
}

void CUnit::ClearIsDead() {
    m_status &= ~0x01;
}

void CUnit::SetRaiseable(int32_t raiseable) {
    if (raiseable) {
        m_flags |= 0x20;
    } else {
        m_flags &= ~0x20;
    }
}

void CUnit::SetNeedsElevPos(int32_t needsElev) {
    if (needsElev) {
        m_flags |= 0x40;
    } else {
        m_flags &= ~0x40;
    }
}

void CUnit::SetOffsetVisual(int32_t offset) {
    (void)offset;
}

void CUnit::SetScaleBullets(int32_t scale) {
    (void)scale;
}

void CUnit::SetImpairedVision(int32_t impaired) {
    (void)impaired;
}

void CUnit::SetReturnGold(int32_t gold) {
    (void)gold;
}

void CUnit::SetReturnLumber(int32_t lumber) {
    (void)lumber;
}

void CUnit::ResetShadow(uint32_t shadowId) {
    (void)shadowId;
}

void CUnit::TaskCompleted() {
    // Task completed
}

void CUnit::LifeListen(int32_t value, const float& delta, int32_t agentId, CAgent* agent, int shareType) {
    (void)value;
    (void)delta;
    (void)agentId;
    (void)agent;
    (void)shareType;
}

void CUnit::ManaListen(int32_t value, const float& delta, int32_t agentId, CAgent* agent, int shareType) {
    (void)value;
    (void)delta;
    (void)agentId;
    (void)agent;
    (void)shareType;
}
