#include <gtest/gtest.h>
#include "Glue/CGlueMgr.h"
#include "Glue/CMainMenu.h"
#include "Glue/CCharacterSelection.h"
#include "Glue/COptionsMenu.h"
#include "Glue/CLoading.h"
#include "Glue/CScoreScreen.h"
#include "Glue/CRealmList.h"
#include "Glue/CTitle.h"

// CGlueMgr tests are in TestCGlueMgr.cpp

// Test CMainMenu
TEST(CMainMenuTest, DefaultConstructor) {
    CMainMenu menu;
    EXPECT_FALSE(menu.IsInitialized());
    EXPECT_TRUE(menu.IsVisible());
}

TEST(CMainMenuTest, Initialize) {
    CMainMenu menu;
    EXPECT_TRUE(menu.Initialize());
    EXPECT_TRUE(menu.IsInitialized());
}

// Test CCharacterSelection
TEST(CCharacterSelectionTest, DefaultConstructor) {
    CCharacterSelection sel;
    EXPECT_FALSE(sel.IsInitialized());
    EXPECT_TRUE(sel.IsVisible());
    EXPECT_EQ(sel.GetSelectedCharacterId(), -1);
}

TEST(CCharacterSelectionTest, Initialize) {
    CCharacterSelection sel;
    EXPECT_TRUE(sel.Initialize());
    EXPECT_TRUE(sel.IsInitialized());
}

TEST(CCharacterSelectionTest, CreateCharacter) {
    CCharacterSelection sel;
    sel.Initialize();
    sel.CreateCharacter("Hero1", 1);
    EXPECT_EQ(sel.GetCharacterCount(), 1u);
    EXPECT_STREQ(sel.GetCharacterName(1), "Hero1");
}

TEST(CCharacterSelectionTest, SelectCharacter) {
    CCharacterSelection sel;
    sel.Initialize();
    sel.CreateCharacter("Hero1", 1);
    sel.SelectCharacter(1);
    EXPECT_EQ(sel.GetSelectedCharacterId(), 1);
}

TEST(CCharacterSelectionTest, DeleteCharacter) {
    CCharacterSelection sel;
    sel.Initialize();
    sel.CreateCharacter("Hero1", 1);
    sel.DeleteCharacter(1);
    EXPECT_EQ(sel.GetCharacterCount(), 0u);
}

// Test COptionsMenu
TEST(COptionsMenuTest, DefaultConstructor) {
    COptionsMenu menu;
    EXPECT_FALSE(menu.IsInitialized());
    EXPECT_FALSE(menu.IsVisible());
    EXPECT_EQ(menu.GetVolume(), 50);
    EXPECT_EQ(menu.GetScreenWidth(), 800);
}

TEST(COptionsMenuTest, Initialize) {
    COptionsMenu menu;
    EXPECT_TRUE(menu.Initialize());
    EXPECT_TRUE(menu.IsInitialized());
}

TEST(COptionsMenuTest, SetVolume) {
    COptionsMenu menu;
    menu.SetVolume(75);
    EXPECT_EQ(menu.GetVolume(), 75);
}

TEST(COptionsMenuTest, SetFullscreen) {
    COptionsMenu menu;
    menu.SetFullscreen(true);
    EXPECT_TRUE(menu.IsFullscreen());
}

TEST(COptionsMenuTest, SetScreenResolution) {
    COptionsMenu menu;
    menu.SetScreenResolution(1920, 1080);
    EXPECT_EQ(menu.GetScreenWidth(), 1920);
    EXPECT_EQ(menu.GetScreenHeight(), 1080);
}

// Test CLoading
TEST(CLoadingTest, DefaultConstructor) {
    CLoading loading;
    EXPECT_FALSE(loading.IsInitialized());
    EXPECT_FALSE(loading.IsLoading());
    EXPECT_FLOAT_EQ(loading.GetProgress(), 0.0f);
}

TEST(CLoadingTest, Initialize) {
    CLoading loading;
    EXPECT_TRUE(loading.Initialize());
    EXPECT_TRUE(loading.IsInitialized());
}

TEST(CLoadingTest, SetProgress) {
    CLoading loading;
    loading.SetProgress(0.5f);
    EXPECT_FLOAT_EQ(loading.GetProgress(), 0.5f);
}

TEST(CLoadingTest, SetLoading) {
    CLoading loading;
    loading.SetLoading(true);
    EXPECT_TRUE(loading.IsLoading());
}

// Test CScoreScreen
TEST(CScoreScreenTest, DefaultConstructor) {
    CScoreScreen screen;
    EXPECT_FALSE(screen.IsInitialized());
    EXPECT_FALSE(screen.IsVisible());
    EXPECT_EQ(screen.GetPlayerCount(), 0u);
}

TEST(CScoreScreenTest, Initialize) {
    CScoreScreen screen;
    EXPECT_TRUE(screen.Initialize());
    EXPECT_TRUE(screen.IsInitialized());
}

TEST(CScoreScreenTest, AddPlayerScore) {
    CScoreScreen screen;
    screen.Initialize();
    screen.AddPlayerScore(1, "Player1", 100);
    screen.AddPlayerScore(2, "Player2", 200);
    EXPECT_EQ(screen.GetPlayerCount(), 2u);
    EXPECT_EQ(screen.GetPlayerScore(0), 200); // Sorted by score
}

TEST(CScoreScreenTest, ClearScores) {
    CScoreScreen screen;
    screen.Initialize();
    screen.AddPlayerScore(1, "Player1", 100);
    screen.ClearScores();
    EXPECT_EQ(screen.GetPlayerCount(), 0u);
}

// Test CRealmList
TEST(CRealmListTest, DefaultConstructor) {
    CRealmList list;
    EXPECT_FALSE(list.IsInitialized());
    EXPECT_FALSE(list.IsVisible());
    EXPECT_EQ(list.GetRealmCount(), 0u);
}

TEST(CRealmListTest, Initialize) {
    CRealmList list;
    EXPECT_TRUE(list.Initialize());
    EXPECT_TRUE(list.IsInitialized());
}

TEST(CRealmListTest, AddRealm) {
    CRealmList list;
    list.Initialize();
    list.AddRealm("Realm1", "192.168.1.1", 6112);
    EXPECT_EQ(list.GetRealmCount(), 1u);
    EXPECT_STREQ(list.GetRealmName(0), "Realm1");
}

TEST(CRealmListTest, RemoveRealm) {
    CRealmList list;
    list.Initialize();
    list.AddRealm("Realm1", "192.168.1.1", 6112);
    list.RemoveRealm("Realm1");
    EXPECT_EQ(list.GetRealmCount(), 0u);
}

// Test CTitle
TEST(CTitleTest, DefaultConstructor) {
    CTitle title;
    EXPECT_FALSE(title.IsInitialized());
    EXPECT_TRUE(title.IsVisible());
}

TEST(CTitleTest, Initialize) {
    CTitle title;
    EXPECT_TRUE(title.Initialize());
    EXPECT_TRUE(title.IsInitialized());
}

TEST(CTitleTest, SetTitle) {
    CTitle title;
    title.SetTitle("Warcraft III");
    EXPECT_STREQ(title.GetTitle(), "Warcraft III");
}

TEST(CTitleTest, SetSubtitle) {
    CTitle title;
    title.SetSubtitle("The Frozen Throne");
    EXPECT_STREQ(title.GetSubtitle(), "The Frozen Throne");
}
