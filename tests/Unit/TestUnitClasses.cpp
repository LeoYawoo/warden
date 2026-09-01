#include <gtest/gtest.h>
#include "Unit/CUnit.h"
#include "Unit/CItem.h"
#include "Unit/CWidget.h"

// Test CUnit
TEST(CUnitTest, DefaultConstructor) {
    CUnit unit;
    EXPECT_EQ(unit.GetUnitId(), 0);
    EXPECT_EQ(unit.GetLevel(), 0);
}

TEST(CUnitTest, DisplaysHP) {
    CUnit unit;
    EXPECT_TRUE(unit.DisplaysHP());
}

TEST(CUnitTest, DisplaysMana) {
    CUnit unit;
    EXPECT_FALSE(unit.DisplaysMana());
}

TEST(CUnitTest, IsHeroUnit) {
    CUnit unit;
    EXPECT_FALSE(unit.IsHeroUnit());
}

TEST(CUnitTest, BaseDefense) {
    CUnit unit;
    EXPECT_EQ(unit.BaseDefense(), 0);
}

TEST(CUnitTest, AcquireRange) {
    CUnit unit;
    EXPECT_FLOAT_EQ(unit.AcquireRange(), 0.0f);
}

TEST(CUnitTest, ClearIsDead) {
    CUnit unit;
    unit.ClearIsDead();
    // Verify no crash
}

TEST(CUnitTest, SetRaiseable) {
    CUnit unit;
    unit.SetRaiseable(1);
    // Verify no crash
}

TEST(CUnitTest, TaskCompleted) {
    CUnit unit;
    unit.TaskCompleted();
    // Verify no crash
}

// Test CItem
TEST(CItemTest, DefaultConstructor) {
    CItem item;
    EXPECT_EQ(item.GetItemId(), 0);
    EXPECT_EQ(item.GetCharges(), 1);
}

TEST(CItemTest, SetItemId) {
    CItem item;
    item.SetItemId(100);
    EXPECT_EQ(item.GetItemId(), 100);
}

TEST(CItemTest, SetItemType) {
    CItem item;
    item.SetItemType(2);
    EXPECT_EQ(item.GetItemType(), 2);
}

TEST(CItemTest, SetCharges) {
    CItem item;
    item.SetCharges(5);
    EXPECT_EQ(item.GetCharges(), 5);
}

TEST(CItemTest, IsPermanent) {
    CItem item;
    EXPECT_FALSE(item.IsPermanent());

    item.SetPermanent(true);
    EXPECT_TRUE(item.IsPermanent());
}

TEST(CItemTest, IsOwned) {
    CItem item;
    EXPECT_FALSE(item.IsOwned());
}

TEST(CItemTest, IsDisposed) {
    CItem item;
    EXPECT_FALSE(item.IsDisposed());

    item.SetDisposed(true);
    EXPECT_TRUE(item.IsDisposed());
}

TEST(CItemTest, GetPosition) {
    CItem item;
    const Position& pos = item.GetPosition();
    (void)pos;
    // Verify no crash
}

// Test CWidget
TEST(CWidgetTest, DefaultConstructor) {
    CWidget widget;
    EXPECT_EQ(widget.GetWidgetId(), 0);
    EXPECT_EQ(widget.GetWidgetType(), 0);
}

TEST(CWidgetTest, SetWidgetId) {
    CWidget widget;
    widget.SetWidgetId(42);
    EXPECT_EQ(widget.GetWidgetId(), 42);
}

TEST(CWidgetTest, SetWidgetType) {
    CWidget widget;
    widget.SetWidgetType(3);
    EXPECT_EQ(widget.GetWidgetType(), 3);
}

TEST(CWidgetTest, IsVisible) {
    CWidget widget;
    EXPECT_FALSE(widget.IsVisible());

    widget.SetVisible(true);
    EXPECT_TRUE(widget.IsVisible());
}

TEST(CWidgetTest, IsEnabled) {
    CWidget widget;
    EXPECT_FALSE(widget.IsEnabled());

    widget.SetEnabled(true);
    EXPECT_TRUE(widget.IsEnabled());
}

TEST(CWidgetTest, SetPosition) {
    CWidget widget;
    widget.SetPosition(10.0f, 20.0f);
    EXPECT_FLOAT_EQ(widget.GetX(), 10.0f);
    EXPECT_FLOAT_EQ(widget.GetY(), 20.0f);
}

TEST(CWidgetTest, SetSize) {
    CWidget widget;
    widget.SetSize(100.0f, 50.0f);
    EXPECT_FLOAT_EQ(widget.GetWidth(), 100.0f);
    EXPECT_FLOAT_EQ(widget.GetHeight(), 50.0f);
}
