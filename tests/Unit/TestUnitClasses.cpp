#include <gtest/gtest.h>
#include "Unit/CAbilityAttack.h"
#include "Unit/CAbilityMove.h"
#include "Unit/CAbilitySilence.h"
#include "Unit/CAbilityCriticalStrike.h"
#include "Unit/CAbilityEvasion.h"
#include "Unit/CAbilityCouple.h"
#include "Unit/CAbilityMassTeleport.h"
#include "Unit/CCustomData.h"
#include "Unit/CDestructable.h"
#include "Unit/CMissile.h"
#include "Unit/CUnitDatabase.h"
#include "Unit/CUnitUI.h"
#include "Unit/NetUnit.h"

// Test CAbilityAttack
TEST(CAbilityAttackTest, DefaultConstructor) {
    CAbilityAttack ability;
    EXPECT_EQ(ability.GetAttackDamage(), 0);
    EXPECT_FLOAT_EQ(ability.GetAttackRange(), 0.0f);
    EXPECT_FALSE(ability.IsAttacking());
}

TEST(CAbilityAttackTest, SetAttackDamage) {
    CAbilityAttack ability;
    ability.SetAttackDamage(100);
    EXPECT_EQ(ability.GetAttackDamage(), 100);
}

TEST(CAbilityAttackTest, SetAttackRange) {
    CAbilityAttack ability;
    ability.SetAttackRange(500.0f);
    EXPECT_FLOAT_EQ(ability.GetAttackRange(), 500.0f);
}

// Test CAbilityMove
TEST(CAbilityMoveTest, DefaultConstructor) {
    CAbilityMove ability;
    EXPECT_FLOAT_EQ(ability.GetMoveSpeed(), 0.0f);
    EXPECT_FALSE(ability.IsMoving());
}

TEST(CAbilityMoveTest, SetMoveSpeed) {
    CAbilityMove ability;
    ability.SetMoveSpeed(300.0f);
    EXPECT_FLOAT_EQ(ability.GetMoveSpeed(), 300.0f);
}

TEST(CAbilityMoveTest, SetTarget) {
    CAbilityMove ability;
    ability.SetTarget(100.0f, 200.0f);
    EXPECT_FLOAT_EQ(ability.GetTargetX(), 100.0f);
    EXPECT_FLOAT_EQ(ability.GetTargetY(), 200.0f);
}

// Test CAbilitySilence
TEST(CAbilitySilenceTest, DefaultConstructor) {
    CAbilitySilence ability;
    EXPECT_FLOAT_EQ(ability.GetDuration(), 0.0f);
    EXPECT_FALSE(ability.IsActive());
}

TEST(CAbilitySilenceTest, SetDuration) {
    CAbilitySilence ability;
    ability.SetDuration(5.0f);
    EXPECT_FLOAT_EQ(ability.GetDuration(), 5.0f);
}

// Test CAbilityCriticalStrike
TEST(CAbilityCriticalStrikeTest, DefaultConstructor) {
    CAbilityCriticalStrike ability;
    EXPECT_FLOAT_EQ(ability.GetChance(), 0.0f);
    EXPECT_FLOAT_EQ(ability.GetMultiplier(), 1.0f);
    EXPECT_FALSE(ability.IsCritical());
}

TEST(CAbilityCriticalStrikeTest, SetChance) {
    CAbilityCriticalStrike ability;
    ability.SetChance(0.25f);
    EXPECT_FLOAT_EQ(ability.GetChance(), 0.25f);
}

// Test CAbilityEvasion
TEST(CAbilityEvasionTest, DefaultConstructor) {
    CAbilityEvasion ability;
    EXPECT_FLOAT_EQ(ability.GetChance(), 0.0f);
    EXPECT_FALSE(ability.IsEvading());
}

TEST(CAbilityEvasionTest, SetChance) {
    CAbilityEvasion ability;
    ability.SetChance(0.3f);
    EXPECT_FLOAT_EQ(ability.GetChance(), 0.3f);
}

// Test CAbilityCouple
TEST(CAbilityCoupleTest, DefaultConstructor) {
    CAbilityCouple ability;
    EXPECT_EQ(ability.GetPartner(), nullptr);
    EXPECT_FLOAT_EQ(ability.GetDistance(), 0.0f);
    EXPECT_FALSE(ability.IsCoupled());
}

TEST(CAbilityCoupleTest, SetDistance) {
    CAbilityCouple ability;
    ability.SetDistance(500.0f);
    EXPECT_FLOAT_EQ(ability.GetDistance(), 500.0f);
}

// Test CAbilityMassTeleport
TEST(CAbilityMassTeleportTest, DefaultConstructor) {
    CAbilityMassTeleport ability;
    EXPECT_FLOAT_EQ(ability.GetRadius(), 0.0f);
    EXPECT_FALSE(ability.IsCasting());
}

TEST(CAbilityMassTeleportTest, SetRadius) {
    CAbilityMassTeleport ability;
    ability.SetRadius(1000.0f);
    EXPECT_FLOAT_EQ(ability.GetRadius(), 1000.0f);
}

TEST(CAbilityMassTeleportTest, SetTarget) {
    CAbilityMassTeleport ability;
    ability.SetTarget(500.0f, 500.0f);
    EXPECT_FLOAT_EQ(ability.GetTargetX(), 500.0f);
    EXPECT_FLOAT_EQ(ability.GetTargetY(), 500.0f);
}

// Test CCustomData
TEST(CCustomDataTest, DefaultConstructor) {
    CCustomData data;
    EXPECT_EQ(data.GetCount(), 0u);
}

TEST(CCustomDataTest, SetGetData) {
    CCustomData data;
    data.SetData("key1", "value1");
    std::string value;
    EXPECT_TRUE(data.GetData("key1", value));
    EXPECT_STREQ(value.c_str(), "value1");
}

TEST(CCustomDataTest, HasData) {
    CCustomData data;
    data.SetData("key1", "value1");
    EXPECT_TRUE(data.HasData("key1"));
    EXPECT_FALSE(data.HasData("key2"));
}

TEST(CCustomDataTest, RemoveData) {
    CCustomData data;
    data.SetData("key1", "value1");
    EXPECT_TRUE(data.RemoveData("key1"));
    EXPECT_FALSE(data.HasData("key1"));
}

// Test CDestructable
TEST(CDestructableTest, DefaultConstructor) {
    CDestructable dest;
    EXPECT_EQ(dest.GetDestructableId(), 0);
    EXPECT_EQ(dest.GetHealth(), 0);
    EXPECT_FALSE(dest.IsInvulnerable());
}

TEST(CDestructableTest, SetHealth) {
    CDestructable dest;
    dest.SetHealth(500);
    EXPECT_EQ(dest.GetHealth(), 500);
}

TEST(CDestructableTest, SetPosition) {
    CDestructable dest;
    dest.SetPosition(100.0f, 200.0f);
    EXPECT_FLOAT_EQ(dest.GetX(), 100.0f);
    EXPECT_FLOAT_EQ(dest.GetY(), 200.0f);
}

// Test CMissile
TEST(CMissileTest, DefaultConstructor) {
    CMissile missile;
    EXPECT_EQ(missile.GetMissileId(), 0);
    EXPECT_FLOAT_EQ(missile.GetSpeed(), 0.0f);
    EXPECT_FALSE(missile.IsActive());
}

TEST(CMissileTest, SetPosition) {
    CMissile missile;
    missile.SetPosition(10.0f, 20.0f, 30.0f);
    EXPECT_FLOAT_EQ(missile.GetX(), 10.0f);
    EXPECT_FLOAT_EQ(missile.GetY(), 20.0f);
    EXPECT_FLOAT_EQ(missile.GetZ(), 30.0f);
}

// Test CUnitDatabase
TEST(CUnitDatabaseTest, DefaultConstructor) {
    CUnitDatabase db;
    EXPECT_FALSE(db.IsInitialized());
    EXPECT_EQ(db.GetUnitTypeCount(), 0);
}

TEST(CUnitDatabaseTest, Initialize) {
    CUnitDatabase db;
    EXPECT_TRUE(db.Initialize());
    EXPECT_TRUE(db.IsInitialized());
}

TEST(CUnitDatabaseTest, RegisterUnitType) {
    CUnitDatabase db;
    db.Initialize();
    EXPECT_TRUE(db.RegisterUnitType(1, "Footman"));
    EXPECT_TRUE(db.HasUnitType(1));
    EXPECT_STREQ(db.GetUnitTypeName(1), "Footman");
}

// Test CUnitUI
TEST(CUnitUITest, DefaultConstructor) {
    CUnitUI ui;
    EXPECT_EQ(ui.GetUnit(), nullptr);
    EXPECT_FALSE(ui.IsSelected());
    EXPECT_FALSE(ui.IsHighlighted());
    EXPECT_TRUE(ui.IsVisible());
}

TEST(CUnitUITest, SetSelected) {
    CUnitUI ui;
    ui.SetSelected(true);
    EXPECT_TRUE(ui.IsSelected());
}

// Test NetUnit
TEST(NetUnitTest, DefaultConstructor) {
    NetUnit unit;
    EXPECT_EQ(unit.GetNetId(), 0);
    EXPECT_EQ(unit.GetOwnerId(), 0);
    EXPECT_FALSE(unit.IsSynced());
}

TEST(NetUnitTest, SetNetId) {
    NetUnit unit;
    unit.SetNetId(42);
    EXPECT_EQ(unit.GetNetId(), 42);
}

TEST(NetUnitTest, SetOwnerId) {
    NetUnit unit;
    unit.SetOwnerId(1);
    EXPECT_EQ(unit.GetOwnerId(), 1);
}
