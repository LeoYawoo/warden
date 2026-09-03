#include <gtest/gtest.h>
#include "Frame/CBackdropGenerator.h"
#include "Frame/CChatDisplay.h"
#include "Frame/CControlSet.h"
#include "Frame/CFramePoint.h"
#include "Frame/CHighlightFrame.h"
#include "Frame/CMenu.h"
#include "Frame/CMessageFrame.h"
#include "Frame/CModelFrame.h"
#include "Frame/CPopupMenu.h"
#include "Frame/CScreenFrame.h"
#include "Frame/CSimpleButton.h"
#include "Frame/CSimpleCheckbox.h"
#include "Frame/CSimpleMessageFrame.h"
#include "Frame/CSimpleRender.h"
#include "Frame/CSimpleStatusBar.h"
#include "Frame/CSimpleTop.h"
#include "Frame/CSpriteFrame.h"
#include "Frame/CTextButtonFrame.h"

// Test CBackdropGenerator
TEST(CBackdropGeneratorTest, DefaultConstructor) {
    CBackdropGenerator gen;
    EXPECT_FALSE(gen.IsGenerated());
}

TEST(CBackdropGeneratorTest, Generate) {
    CBackdropGenerator gen;
    EXPECT_TRUE(gen.Generate());
    EXPECT_TRUE(gen.IsGenerated());
}

// Test CChatDisplay
TEST(CChatDisplayTest, DefaultConstructor) {
    CChatDisplay display;
    EXPECT_EQ(display.GetMessageCount(), 0u);
    EXPECT_TRUE(display.GetShowTimestamps());
}

TEST(CChatDisplayTest, AddMessage) {
    CChatDisplay display;
    display.AddMessage("User1", "Hello");
    EXPECT_EQ(display.GetMessageCount(), 1u);
    EXPECT_STREQ(display.GetMessageSender(0), "User1");
}

TEST(CChatDisplayTest, ClearMessages) {
    CChatDisplay display;
    display.AddMessage("User1", "Hello");
    display.ClearMessages();
    EXPECT_EQ(display.GetMessageCount(), 0u);
}

// Test CControlSet
TEST(CControlSetTest, DefaultConstructor) {
    CControlSet set;
    EXPECT_TRUE(set.IsEmpty());
    EXPECT_EQ(set.GetControlCount(), 0u);
}

TEST(CControlSetTest, AddControl) {
    CControlSet set;
    CControl control;
    set.AddControl(&control);
    EXPECT_EQ(set.GetControlCount(), 1u);
}

// Test CFramePoint
TEST(CFramePointTest, DefaultConstructor) {
    CFramePoint point;
    EXPECT_FLOAT_EQ(point.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(point.GetY(), 0.0f);
}

TEST(CFramePointTest, SetPosition) {
    CFramePoint point;
    point.SetPosition(10, 20);
    EXPECT_FLOAT_EQ(point.GetX(), 10.0f);
    EXPECT_FLOAT_EQ(point.GetY(), 20.0f);
}

// Test CHighlightFrame
TEST(CHighlightFrameTest, DefaultConstructor) {
    CHighlightFrame frame;
    EXPECT_FALSE(frame.IsHighlighted());
}

TEST(CHighlightFrameTest, SetHighlighted) {
    CHighlightFrame frame;
    frame.SetHighlighted(true);
    EXPECT_TRUE(frame.IsHighlighted());
}

// Test CMenu
TEST(CMenuTest, DefaultConstructor) {
    CMenu menu;
    EXPECT_EQ(menu.GetItemCount(), 0u);
    EXPECT_FALSE(menu.IsOpen());
}

TEST(CMenuTest, AddItem) {
    CMenu menu;
    menu.AddItem("File", 1);
    menu.AddItem("Edit", 2);
    EXPECT_EQ(menu.GetItemCount(), 2u);
}

TEST(CMenuTest, RemoveItem) {
    CMenu menu;
    menu.AddItem("File", 1);
    menu.AddItem("Edit", 2);
    menu.RemoveItem(1);
    EXPECT_EQ(menu.GetItemCount(), 1u);
}

// Test CMessageFrame
TEST(CMessageFrameTest, DefaultConstructor) {
    CMessageFrame frame;
    EXPECT_EQ(frame.GetMessageType(), 0);
}

TEST(CMessageFrameTest, ShowMessage) {
    CMessageFrame frame;
    frame.ShowMessage("Test message", 1);
    EXPECT_STREQ(frame.GetMessage(), "Test message");
    EXPECT_EQ(frame.GetMessageType(), 1);
    EXPECT_TRUE(frame.IsVisible());
}

// Test CModelFrame
TEST(CModelFrameTest, DefaultConstructor) {
    CModelFrame frame;
    EXPECT_FALSE(frame.IsPlaying());
    EXPECT_FLOAT_EQ(frame.GetScale(), 1.0f);
}

TEST(CModelFrameTest, SetModelFile) {
    CModelFrame frame;
    frame.SetModelFile("model.mdx");
    EXPECT_STREQ(frame.GetModelFile(), "model.mdx");
}

// Test CPopupMenu
TEST(CPopupMenuTest, DefaultConstructor) {
    CPopupMenu menu;
    EXPECT_FLOAT_EQ(menu.GetPopupX(), 0.0f);
    EXPECT_FLOAT_EQ(menu.GetPopupY(), 0.0f);
}

TEST(CPopupMenuTest, Show) {
    CPopupMenu menu;
    menu.Show(100, 200);
    EXPECT_FLOAT_EQ(menu.GetPopupX(), 100.0f);
    EXPECT_TRUE(menu.IsOpen());
}

// Test CScreenFrame
TEST(CScreenFrameTest, DefaultConstructor) {
    CScreenFrame frame;
    EXPECT_EQ(frame.GetScreenWidth(), 800);
    EXPECT_EQ(frame.GetScreenHeight(), 600);
}

TEST(CScreenFrameTest, SetScreenSize) {
    CScreenFrame frame;
    frame.SetScreenSize(1920, 1080);
    EXPECT_EQ(frame.GetScreenWidth(), 1920);
    EXPECT_EQ(frame.GetScreenHeight(), 1080);
}

// Test CSimpleButton
TEST(CSimpleButtonTest, DefaultConstructor) {
    CSimpleButton button;
    EXPECT_FALSE(button.IsDisabled());
}

TEST(CSimpleButtonTest, SetDisabled) {
    CSimpleButton button;
    button.SetDisabled(true);
    EXPECT_TRUE(button.IsDisabled());
}

// Test CSimpleCheckbox
TEST(CSimpleCheckboxTest, DefaultConstructor) {
    CSimpleCheckbox checkbox;
    // Verify construction doesn't crash
}

// Test CSimpleMessageFrame
TEST(CSimpleMessageFrameTest, DefaultConstructor) {
    CSimpleMessageFrame frame;
    // Verify construction doesn't crash
}

// Test CSimpleRender
TEST(CSimpleRenderTest, DefaultConstructor) {
    CSimpleRender render;
    EXPECT_FLOAT_EQ(render.GetAlpha(), 1.0f);
}

TEST(CSimpleRenderTest, SetAlpha) {
    CSimpleRender render;
    render.SetAlpha(0.5f);
    EXPECT_FLOAT_EQ(render.GetAlpha(), 0.5f);
}

// Test CSimpleStatusBar
TEST(CSimpleStatusBarTest, DefaultConstructor) {
    CSimpleStatusBar statusBar;
    EXPECT_FLOAT_EQ(statusBar.GetProgress(), 0.0f);
}

TEST(CSimpleStatusBarTest, SetProgress) {
    CSimpleStatusBar statusBar;
    statusBar.SetProgress(0.75f);
    EXPECT_FLOAT_EQ(statusBar.GetProgress(), 0.75f);
}

// Test CSimpleTop
TEST(CSimpleTopTest, DefaultConstructor) {
    CSimpleTop top;
    EXPECT_EQ(top.GetTopFrame(), &top);
}

// Test CSpriteFrame
TEST(CSpriteFrameTest, DefaultConstructor) {
    CSpriteFrame frame;
    EXPECT_FALSE(frame.IsPlaying());
}

TEST(CSpriteFrameTest, SetSpriteFile) {
    CSpriteFrame frame;
    frame.SetSpriteFile("sprite.blp");
    EXPECT_STREQ(frame.GetSpriteFile(), "sprite.blp");
}

// Test CTextButtonFrame
TEST(CTextButtonFrameTest, DefaultConstructor) {
    CTextButtonFrame button;
    // Verify construction doesn't crash
}
