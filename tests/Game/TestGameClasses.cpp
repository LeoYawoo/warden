#include <gtest/gtest.h>
#include "Game/CGameState.h"
#include "Game/CGameWar3.h"
#include "Game/CPlayerWar3.h"
#include "Game/CGroup.h"
#include "Game/CLeaderboardWar3.h"
#include "Game/CMultiboardWar3.h"
#include "Game/CSelectionWar3.h"
#include "Game/CPreloadManager.h"

// Test CGameState
TEST(CGameStateTest, DefaultConstructor) {
    CGameState state;
    EXPECT_FALSE(state.IsInitialized());
    EXPECT_FLOAT_EQ(state.GetGameTime(), 0.0f);
    EXPECT_FLOAT_EQ(state.GetGameSpeed(), 1.0f);
    EXPECT_FALSE(state.IsPaused());
}

TEST(CGameStateTest, Initialize) {
    CGameState state;
    state.Initialize();
    EXPECT_TRUE(state.IsInitialized());
}

TEST(CGameStateTest, UpdateGameTime) {
    CGameState state;
    state.Initialize();
    state.UpdateGameTime(1.0f);
    EXPECT_FLOAT_EQ(state.GetGameTime(), 1.0f);
}

TEST(CGameStateTest, SetPaused) {
    CGameState state;
    state.Initialize();
    state.SetPaused(true);
    EXPECT_TRUE(state.IsPaused());
    state.UpdateGameTime(1.0f);
    EXPECT_FLOAT_EQ(state.GetGameTime(), 0.0f);
}

// Test CGameWar3
TEST(CGameWar3Test, DefaultConstructor) {
    CGameWar3 game;
    EXPECT_FALSE(game.IsInitialized());
    EXPECT_FALSE(game.IsGameRunning());
}

TEST(CGameWar3Test, Initialize) {
    CGameWar3 game;
    EXPECT_TRUE(game.Initialize());
    EXPECT_TRUE(game.IsInitialized());
}

TEST(CGameWar3Test, StartEndGame) {
    CGameWar3 game;
    game.Initialize();
    game.StartGame();
    EXPECT_TRUE(game.IsGameRunning());
    game.EndGame();
    EXPECT_FALSE(game.IsGameRunning());
}

// Test CPlayerWar3
TEST(CPlayerWar3Test, DefaultConstructor) {
    CPlayerWar3 player;
    EXPECT_EQ(player.GetPlayerId(), 0);
    EXPECT_TRUE(player.IsHuman());
    EXPECT_EQ(player.GetGold(), 0);
    EXPECT_EQ(player.GetFoodCap(), 10);
}

TEST(CPlayerWar3Test, AddGold) {
    CPlayerWar3 player;
    player.AddGold(100);
    EXPECT_EQ(player.GetGold(), 100);
    player.AddGold(50);
    EXPECT_EQ(player.GetGold(), 150);
}

TEST(CPlayerWar3Test, AddLumber) {
    CPlayerWar3 player;
    player.AddLumber(50);
    EXPECT_EQ(player.GetLumber(), 50);
}

TEST(CPlayerWar3Test, AddFoodCap) {
    CPlayerWar3 player;
    player.AddFoodCap(5);
    EXPECT_EQ(player.GetFoodCap(), 15);
}

// Test CGroup
TEST(CGroupTest, DefaultConstructor) {
    CGroup group;
    EXPECT_EQ(group.GetUnitCount(), 0u);
}

TEST(CGroupTest, AddUnit) {
    CGroup group;
    // CUnit is forward declared, use nullptr for test
    group.AddUnit(nullptr);
    // Verify no crash
}

// Test CLeaderboardWar3
TEST(CLeaderboardWar3Test, DefaultConstructor) {
    CLeaderboardWar3 lb;
    EXPECT_TRUE(lb.IsVisible());
    EXPECT_EQ(lb.GetEntryCount(), 0u);
}

TEST(CLeaderboardWar3Test, AddEntry) {
    CLeaderboardWar3 lb;
    lb.AddEntry(1, 100);
    lb.AddEntry(2, 200);
    EXPECT_EQ(lb.GetEntryCount(), 2u);
    EXPECT_EQ(lb.GetEntryScore(0), 200); // Sorted by score descending
}

TEST(CLeaderboardWar3Test, RemoveEntry) {
    CLeaderboardWar3 lb;
    lb.AddEntry(1, 100);
    lb.RemoveEntry(1);
    EXPECT_EQ(lb.GetEntryCount(), 0u);
}

// Test CMultiboardWar3
TEST(CMultiboardWar3Test, DefaultConstructor) {
    CMultiboardWar3 mb;
    EXPECT_TRUE(mb.IsVisible());
    EXPECT_FALSE(mb.IsMinimized());
}

TEST(CMultiboardWar3Test, SetDimensions) {
    CMultiboardWar3 mb;
    mb.SetDimensions(3, 4);
    EXPECT_EQ(mb.GetRowCount(), 3);
    EXPECT_EQ(mb.GetColumnCount(), 4);
}

TEST(CMultiboardWar3Test, SetItemTitle) {
    CMultiboardWar3 mb;
    mb.SetDimensions(2, 2);
    mb.SetItemTitle(0, 0, "Title");
    // Verify no crash
}

// Test CSelectionWar3
TEST(CSelectionWar3Test, DefaultConstructor) {
    CSelectionWar3 sel;
    EXPECT_EQ(sel.GetSelectionCount(), 0u);
    EXPECT_TRUE(sel.IsMultiSelect());
}

TEST(CSelectionWar3Test, ClearSelection) {
    CSelectionWar3 sel;
    sel.ClearSelection();
    EXPECT_EQ(sel.GetSelectionCount(), 0u);
}

// Test CPreloadManager
TEST(CPreloadManagerTest, DefaultConstructor) {
    CPreloadManager pm;
    EXPECT_FALSE(pm.IsPreloading());
    EXPECT_TRUE(pm.IsAutoPreload());
    EXPECT_EQ(pm.GetPreloadCount(), 0u);
}

TEST(CPreloadManagerTest, PreloadFile) {
    CPreloadManager pm;
    pm.PreloadFile("test.blp");
    EXPECT_EQ(pm.GetPreloadCount(), 1u);
}

TEST(CPreloadManagerTest, SetAutoPreload) {
    CPreloadManager pm;
    pm.SetAutoPreload(false);
    EXPECT_FALSE(pm.IsAutoPreload());
}
