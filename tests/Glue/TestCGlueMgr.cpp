#include <gtest/gtest.h>
#include "Glue/CGlueMgr.h"

TEST(CGlueMgrTest, DefaultConstructor) {
    CGlueMgr mgr;
    EXPECT_FALSE(mgr.IsInitialized());
    EXPECT_FALSE(mgr.IsTransitioning());
}

TEST(CGlueMgrTest, Initialize) {
    CGlueMgr mgr;
    EXPECT_TRUE(mgr.Initialize());
    EXPECT_TRUE(mgr.IsInitialized());
}

TEST(CGlueMgrTest, ShowMainMenu) {
    CGlueMgr mgr;
    mgr.Initialize();
    mgr.ShowMainMenu();
    EXPECT_EQ(mgr.GetCurrentScreen(), CGlueMgr::SCREEN_MAIN_MENU);
}

TEST(CGlueMgrTest, ShowCharacterSelection) {
    CGlueMgr mgr;
    mgr.Initialize();
    mgr.ShowCharacterSelection();
    EXPECT_EQ(mgr.GetCurrentScreen(), CGlueMgr::SCREEN_CHARACTER_SELECTION);
}

TEST(CGlueMgrTest, GetCurrentScreenName) {
    CGlueMgr mgr;
    mgr.Initialize();
    mgr.ShowMainMenu();
    EXPECT_STREQ(mgr.GetCurrentScreenName(), "MainMenu");
}
