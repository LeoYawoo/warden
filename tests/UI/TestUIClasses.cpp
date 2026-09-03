#include <gtest/gtest.h>
#include "UI/CGameUI.h"
#include "UI/CResourceBar.h"
#include "UI/CHeroBar.h"
#include "UI/CMinimap.h"
#include "UI/CCommandBar.h"
#include "UI/CPortraitButton.h"
#include "UI/CProgressIndicator.h"
#include "UI/CInfoBar.h"
#include "UI/CInfoPanelUnitDetail.h"

// Test CGameUI
TEST(CGameUITest, DefaultConstructor) {
    CGameUI ui;
    EXPECT_FALSE(ui.IsInitialized());
    EXPECT_TRUE(ui.IsVisible());
    EXPECT_FALSE(ui.IsChatVisible());
}

TEST(CGameUITest, Initialize) {
    CGameUI ui;
    EXPECT_TRUE(ui.Initialize());
    EXPECT_TRUE(ui.IsInitialized());
}

TEST(CGameUITest, SetVisible) {
    CGameUI ui;
    ui.SetVisible(false);
    EXPECT_FALSE(ui.IsVisible());
}

TEST(CGameUITest, SetChatVisible) {
    CGameUI ui;
    ui.SetChatVisible(true);
    EXPECT_TRUE(ui.IsChatVisible());
}

// Test CResourceBar
TEST(CResourceBarTest, DefaultConstructor) {
    CResourceBar bar;
    EXPECT_EQ(bar.GetGold(), 0);
    EXPECT_EQ(bar.GetLumber(), 0);
    EXPECT_EQ(bar.GetFood(), 0);
    EXPECT_EQ(bar.GetFoodCap(), 10);
    EXPECT_TRUE(bar.IsVisible());
}

TEST(CResourceBarTest, SetGold) {
    CResourceBar bar;
    bar.SetGold(1000);
    EXPECT_EQ(bar.GetGold(), 1000);
}

TEST(CResourceBarTest, SetLumber) {
    CResourceBar bar;
    bar.SetLumber(500);
    EXPECT_EQ(bar.GetLumber(), 500);
}

TEST(CResourceBarTest, SetFood) {
    CResourceBar bar;
    bar.SetFood(20, 30);
    EXPECT_EQ(bar.GetFood(), 20);
    EXPECT_EQ(bar.GetFoodCap(), 30);
}

// Test CHeroBar
TEST(CHeroBarTest, DefaultConstructor) {
    CHeroBar bar;
    EXPECT_EQ(bar.GetHeroCount(), 0u);
    EXPECT_TRUE(bar.IsVisible());
}

TEST(CHeroBarTest, SetVisible) {
    CHeroBar bar;
    bar.SetVisible(false);
    EXPECT_FALSE(bar.IsVisible());
}

// Test CMinimap
TEST(CMinimapTest, DefaultConstructor) {
    CMinimap minimap;
    EXPECT_EQ(minimap.GetWidth(), 200);
    EXPECT_EQ(minimap.GetHeight(), 200);
    EXPECT_TRUE(minimap.IsVisible());
}

TEST(CMinimapTest, SetSize) {
    CMinimap minimap;
    minimap.SetSize(300, 300);
    EXPECT_EQ(minimap.GetWidth(), 300);
    EXPECT_EQ(minimap.GetHeight(), 300);
}

// Test CCommandBar
TEST(CCommandBarTest, DefaultConstructor) {
    CCommandBar bar;
    EXPECT_EQ(bar.GetSelectedUnit(), nullptr);
    EXPECT_TRUE(bar.IsVisible());
}

TEST(CCommandBarTest, SetVisible) {
    CCommandBar bar;
    bar.SetVisible(false);
    EXPECT_FALSE(bar.IsVisible());
}

// Test CPortraitButton
TEST(CPortraitButtonTest, DefaultConstructor) {
    CPortraitButton button;
    EXPECT_EQ(button.GetUnit(), nullptr);
    EXPECT_TRUE(button.IsVisible());
    EXPECT_FALSE(button.IsPlaying());
}

TEST(CPortraitButtonTest, SetVisible) {
    CPortraitButton button;
    button.SetVisible(false);
    EXPECT_FALSE(button.IsVisible());
}

TEST(CPortraitButtonTest, SetPlaying) {
    CPortraitButton button;
    button.SetPlaying(true);
    EXPECT_TRUE(button.IsPlaying());
}

// Test CProgressIndicator
TEST(CProgressIndicatorTest, DefaultConstructor) {
    CProgressIndicator indicator;
    EXPECT_FLOAT_EQ(indicator.GetProgress(), 0.0f);
    EXPECT_TRUE(indicator.IsVisible());
    EXPECT_FALSE(indicator.IsAnimating());
}

TEST(CProgressIndicatorTest, SetProgress) {
    CProgressIndicator indicator;
    indicator.SetProgress(0.75f);
    EXPECT_FLOAT_EQ(indicator.GetProgress(), 0.75f);
}

TEST(CProgressIndicatorTest, SetAnimating) {
    CProgressIndicator indicator;
    indicator.SetAnimating(true);
    EXPECT_TRUE(indicator.IsAnimating());
}

// Test CInfoBar
TEST(CInfoBarTest, DefaultConstructor) {
    CInfoBar bar;
    EXPECT_TRUE(bar.IsVisible());
}

TEST(CInfoBarTest, SetInfoText) {
    CInfoBar bar;
    bar.SetInfoText("Test Info");
    EXPECT_STREQ(bar.GetInfoText(), "Test Info");
}

// Test CInfoPanelUnitDetail
TEST(CInfoPanelUnitDetailTest, DefaultConstructor) {
    CInfoPanelUnitDetail panel;
    EXPECT_EQ(panel.GetUnit(), nullptr);
    EXPECT_TRUE(panel.IsVisible());
}

TEST(CInfoPanelUnitDetailTest, SetVisible) {
    CInfoPanelUnitDetail panel;
    panel.SetVisible(false);
    EXPECT_FALSE(panel.IsVisible());
}
