#include <gtest/gtest.h>
#include "Agile/TInstanceCache.h"
#include "Agile/CAbility.h"
#include "Agile/CAbilityInterfaced.h"
#include "Agile/CAbilityBaseBuild.h"
#include "Agile/CAbilityBaseSell.h"

// Test TInstanceCache
TEST(TInstanceCacheTest, DefaultConstructor) {
    TInstanceCache<int> cache;
    EXPECT_EQ(cache.GetCount(), 0);
    EXPECT_EQ(cache.GetCapacity(), 0);
}

TEST(TInstanceCacheTest, GetInstance) {
    TInstanceCache<int> cache(10);
    int* instance = cache.Get();
    EXPECT_NE(instance, nullptr);
    EXPECT_EQ(cache.GetCount(), 1);
}

TEST(TInstanceCacheTest, GetMultipleInstances) {
    TInstanceCache<int> cache(10);
    int* inst1 = cache.Get();
    int* inst2 = cache.Get();
    int* inst3 = cache.Get();

    EXPECT_NE(inst1, nullptr);
    EXPECT_NE(inst2, nullptr);
    EXPECT_NE(inst3, nullptr);
    EXPECT_EQ(cache.GetCount(), 3);
}

TEST(TInstanceCacheTest, Clear) {
    TInstanceCache<int> cache(10);
    cache.Get();
    cache.Get();
    EXPECT_EQ(cache.GetCount(), 2);

    cache.Clear();
    EXPECT_EQ(cache.GetCount(), 0);
}

// Test CAbility
TEST(CAbilityTest, DefaultConstructor) {
    CAbility ability;
    EXPECT_FALSE(ability.IsActive());
    EXPECT_EQ(ability.GetLevel(), 0);
    EXPECT_FLOAT_EQ(ability.GetCooldown(), 0.0f);
    EXPECT_FALSE(ability.IsOnCooldown());
}

TEST(CAbilityTest, ActivateDeactivate) {
    CAbility ability;
    ability.Activate();
    EXPECT_TRUE(ability.IsActive());

    ability.Deactivate();
    EXPECT_FALSE(ability.IsActive());
}

TEST(CAbilityTest, SetLevel) {
    CAbility ability;
    // Default maxLevel is 0, so SetLevel(5) should fail
    ability.SetLevel(5);
    EXPECT_EQ(ability.GetLevel(), 0);

    // Set a valid level (0 is valid)
    ability.SetLevel(0);
    EXPECT_EQ(ability.GetLevel(), 0);
}

TEST(CAbilityTest, SetCooldown) {
    CAbility ability;
    ability.SetCooldown(10.0f);
    EXPECT_FLOAT_EQ(ability.GetCooldown(), 10.0f);
    EXPECT_TRUE(ability.IsOnCooldown());
}

TEST(CAbilityTest, UpdateCooldown) {
    CAbility ability;
    ability.SetCooldown(5.0f);

    ability.UpdateCooldown(2.0f);
    EXPECT_TRUE(ability.IsOnCooldown());

    ability.UpdateCooldown(4.0f);
    EXPECT_FALSE(ability.IsOnCooldown());
}

// Test CAbilityInterfaced
TEST(CAbilityInterfacedTest, DefaultConstructor) {
    CAbilityInterfaced ability;
    EXPECT_FALSE(ability.HasInterface());
    EXPECT_EQ(ability.GetInterfaceState(), 0);
}

TEST(CAbilityInterfacedTest, SetInterfaceState) {
    CAbilityInterfaced ability;
    ability.SetInterfaceState(1);
    EXPECT_TRUE(ability.HasInterface());
    EXPECT_EQ(ability.GetInterfaceState(), 1);
}

// Test CAbilityBaseBuild
TEST(CAbilityBaseBuildTest, DefaultConstructor) {
    CAbilityBaseBuild ability;
    EXPECT_FLOAT_EQ(ability.GetBuildProgress(), 0.0f);
    EXPECT_FLOAT_EQ(ability.GetBuildTime(), 0.0f);
}

TEST(CAbilityBaseBuildTest, SetBuildProgress) {
    CAbilityBaseBuild ability;
    ability.SetBuildProgress(0.5f);
    EXPECT_FLOAT_EQ(ability.GetBuildProgress(), 0.5f);
}

TEST(CAbilityBaseBuildTest, SetBuildTime) {
    CAbilityBaseBuild ability;
    ability.SetBuildTime(10.0f);
    EXPECT_FLOAT_EQ(ability.GetBuildTime(), 10.0f);
}

TEST(CAbilityBaseBuildTest, IsValidId) {
    EXPECT_TRUE(CAbilityBaseBuild::IsValidId(0));
    EXPECT_TRUE(CAbilityBaseBuild::IsValidId(100));
}

// Test CAbilityBaseSell
TEST(CAbilityBaseSellTest, DefaultConstructor) {
    CAbilityBaseSell ability;
    EXPECT_EQ(ability.GetStockCount(), 0);
    EXPECT_FLOAT_EQ(ability.GetStockRegenTime(), 0.0f);
}

TEST(CAbilityBaseSellTest, SetStockCount) {
    CAbilityBaseSell ability;
    ability.SetStockCount(10);
    EXPECT_EQ(ability.GetStockCount(), 10);
}

TEST(CAbilityBaseSellTest, SetStockRegenTime) {
    CAbilityBaseSell ability;
    ability.SetStockRegenTime(5.0f);
    EXPECT_FLOAT_EQ(ability.GetStockRegenTime(), 5.0f);
}

TEST(CAbilityBaseSellTest, StockFlags) {
    CAbilityBaseSell ability;

    ability.SetStockFlag(0, 0x01);
    EXPECT_TRUE(ability.TestStockFlag(0, 0x01));
    EXPECT_FALSE(ability.TestStockFlag(0, 0x02));

    ability.ClearStockFlag(0, 0x01);
    EXPECT_FALSE(ability.TestStockFlag(0, 0x01));
}

TEST(CAbilityBaseSellTest, StockFlagsBounds) {
    CAbilityBaseSell ability;

    // Test out of bounds
    ability.SetStockFlag(-1, 0x01);
    EXPECT_FALSE(ability.TestStockFlag(-1, 0x01));

    ability.SetStockFlag(32, 0x01);
    EXPECT_FALSE(ability.TestStockFlag(32, 0x01));
}
