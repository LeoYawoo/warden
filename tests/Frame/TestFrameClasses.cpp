#include <gtest/gtest.h>
#include "Frame/CFrame.h"
#include "Frame/CSimpleFrame.h"
#include "Frame/CControl.h"
#include "Frame/CButtonFrame.h"
#include "Frame/CCheckBox.h"
#include "Frame/CEditBox.h"
#include "Frame/CListBox.h"
#include "Frame/CScrollBar.h"
#include "Frame/CSlider.h"
#include "Frame/CTextArea.h"
#include "Frame/CTextFrame.h"
#include "Frame/CLayer.h"
#include "Frame/CDialog.h"

// Test CFrame
TEST(CFrameTest, DefaultConstructor) {
    CFrame frame;
    EXPECT_EQ(frame.GetFrameId(), 0);
    EXPECT_TRUE(frame.IsVisible());
    EXPECT_TRUE(frame.IsEnabled());
    EXPECT_FLOAT_EQ(frame.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(frame.GetY(), 0.0f);
}

TEST(CFrameTest, SetPosition) {
    CFrame frame;
    frame.SetPosition(10, 20);
    EXPECT_FLOAT_EQ(frame.GetX(), 10.0f);
    EXPECT_FLOAT_EQ(frame.GetY(), 20.0f);
}

TEST(CFrameTest, SetSize) {
    CFrame frame;
    frame.SetSize(100, 50);
    EXPECT_FLOAT_EQ(frame.GetWidth(), 100.0f);
    EXPECT_FLOAT_EQ(frame.GetHeight(), 50.0f);
}

TEST(CFrameTest, AddChild) {
    CFrame parent;
    CFrame child;
    parent.AddChild(&child);
    EXPECT_EQ(parent.GetChildCount(), 1u);
    EXPECT_EQ(child.GetParent(), &parent);
}

TEST(CFrameTest, RemoveChild) {
    CFrame parent;
    CFrame child;
    parent.AddChild(&child);
    parent.RemoveChild(&child);
    EXPECT_EQ(parent.GetChildCount(), 0u);
    EXPECT_EQ(child.GetParent(), nullptr);
}

TEST(CFrameTest, GetChildByNameNotFound) {
    CFrame parent;
    CFrame* found = parent.GetChildByName("NonExistent");
    EXPECT_EQ(found, nullptr);
}

// Test CSimpleFrame
TEST(CSimpleFrameTest, DefaultConstructor) {
    CSimpleFrame frame;
    EXPECT_EQ(frame.GetFrameLevel(), 0);
    EXPECT_TRUE(frame.IsMouseEnabled());
    EXPECT_TRUE(frame.IsKeyboardEnabled());
}

TEST(CSimpleFrameTest, SetFrameLevel) {
    CSimpleFrame frame;
    frame.SetFrameLevel(5);
    EXPECT_EQ(frame.GetFrameLevel(), 5);
}

// Test CControl
TEST(CControlTest, DefaultConstructor) {
    CControl control;
    EXPECT_FALSE(control.IsFocused());
}

TEST(CControlTest, SetFocused) {
    CControl control;
    control.SetFocused(true);
    EXPECT_TRUE(control.IsFocused());
}

// Test CButtonFrame
TEST(CButtonFrameTest, DefaultConstructor) {
    CButtonFrame button;
    EXPECT_FALSE(button.IsPressed());
}

TEST(CButtonFrameTest, SetButtonText) {
    CButtonFrame button;
    button.SetButtonText("Click Me");
    EXPECT_STREQ(button.GetButtonText(), "Click Me");
}

TEST(CButtonFrameTest, OnClick) {
    CButtonFrame button;
    button.OnClick();
    EXPECT_TRUE(button.IsPressed());
    button.OnClick();
    EXPECT_FALSE(button.IsPressed());
}

// Test CCheckBox
TEST(CCheckBoxTest, DefaultConstructor) {
    CCheckBox checkbox;
    EXPECT_FALSE(checkbox.IsChecked());
}

TEST(CCheckBoxTest, SetChecked) {
    CCheckBox checkbox;
    checkbox.SetChecked(true);
    EXPECT_TRUE(checkbox.IsChecked());
}

TEST(CCheckBoxTest, OnClick) {
    CCheckBox checkbox;
    checkbox.OnClick();
    EXPECT_TRUE(checkbox.IsChecked());
    checkbox.OnClick();
    EXPECT_FALSE(checkbox.IsChecked());
}

// Test CEditBox
TEST(CEditBoxTest, DefaultConstructor) {
    CEditBox editbox;
    EXPECT_EQ(editbox.GetMaxLength(), 256);
    EXPECT_FALSE(editbox.IsPassword());
}

TEST(CEditBoxTest, SetText) {
    CEditBox editbox;
    editbox.SetText("Hello");
    EXPECT_STREQ(editbox.GetText(), "Hello");
}

// Test CListBox
TEST(CListBoxTest, DefaultConstructor) {
    CListBox listbox;
    EXPECT_EQ(listbox.GetItemCount(), 0u);
    EXPECT_EQ(listbox.GetSelectedIndex(), -1);
}

TEST(CListBoxTest, AddItem) {
    CListBox listbox;
    listbox.AddItem("Item 1");
    listbox.AddItem("Item 2");
    EXPECT_EQ(listbox.GetItemCount(), 2u);
    EXPECT_STREQ(listbox.GetItem(0), "Item 1");
}

TEST(CListBoxTest, RemoveItem) {
    CListBox listbox;
    listbox.AddItem("Item 1");
    listbox.AddItem("Item 2");
    listbox.RemoveItem(0);
    EXPECT_EQ(listbox.GetItemCount(), 1u);
}

// Test CScrollBar
TEST(CScrollBarTest, DefaultConstructor) {
    CScrollBar scrollbar;
    EXPECT_FLOAT_EQ(scrollbar.GetScrollPosition(), 0.0f);
    EXPECT_FLOAT_EQ(scrollbar.GetScrollRange(), 100.0f);
    EXPECT_TRUE(scrollbar.IsVertical());
}

TEST(CScrollBarTest, ScrollUp) {
    CScrollBar scrollbar;
    scrollbar.SetScrollPosition(50);
    scrollbar.ScrollUp(10);
    EXPECT_FLOAT_EQ(scrollbar.GetScrollPosition(), 40.0f);
}

TEST(CScrollBarTest, ScrollDown) {
    CScrollBar scrollbar;
    scrollbar.ScrollDown(10);
    EXPECT_FLOAT_EQ(scrollbar.GetScrollPosition(), 10.0f);
}

// Test CSlider
TEST(CSliderTest, DefaultConstructor) {
    CSlider slider;
    EXPECT_FLOAT_EQ(slider.GetValue(), 0.0f);
    EXPECT_FLOAT_EQ(slider.GetMinValue(), 0.0f);
    EXPECT_FLOAT_EQ(slider.GetMaxValue(), 100.0f);
}

TEST(CSliderTest, SetValue) {
    CSlider slider;
    slider.SetValue(50);
    EXPECT_FLOAT_EQ(slider.GetValue(), 50.0f);
}

TEST(CSliderTest, StepUp) {
    CSlider slider;
    slider.StepUp();
    EXPECT_FLOAT_EQ(slider.GetValue(), 1.0f);
}

// Test CTextArea
TEST(CTextAreaTest, DefaultConstructor) {
    CTextArea textarea;
    EXPECT_EQ(textarea.GetCursorPosition(), 0);
    EXPECT_FALSE(textarea.IsReadOnly());
}

TEST(CTextAreaTest, SetText) {
    CTextArea textarea;
    textarea.SetText("Hello");
    EXPECT_STREQ(textarea.GetText(), "Hello");
}

TEST(CTextAreaTest, AppendText) {
    CTextArea textarea;
    textarea.SetText("Hello");
    textarea.AppendText(" World");
    EXPECT_STREQ(textarea.GetText(), "Hello World");
}

// Test CTextFrame
TEST(CTextFrameTest, DefaultConstructor) {
    CTextFrame textframe;
    EXPECT_EQ(textframe.GetHJust(), 0);
    EXPECT_EQ(textframe.GetVJust(), 0);
}

TEST(CTextFrameTest, SetText) {
    CTextFrame textframe;
    textframe.SetText("Test Text");
    EXPECT_STREQ(textframe.GetText(), "Test Text");
}

// Test CLayer
TEST(CLayerTest, DefaultConstructor) {
    CLayer layer;
    EXPECT_TRUE(layer.IsVisible());
    EXPECT_EQ(layer.GetFrameCount(), 0u);
}

TEST(CLayerTest, AddFrame) {
    CLayer layer;
    CSimpleFrame frame;
    layer.AddFrame(&frame);
    EXPECT_EQ(layer.GetFrameCount(), 1u);
}

// Test CDialog
TEST(CDialogTest, DefaultConstructor) {
    CDialog dialog;
    EXPECT_FALSE(dialog.IsModal());
    EXPECT_EQ(dialog.GetResult(), 0);
}

TEST(CDialogTest, SetTitle) {
    CDialog dialog;
    dialog.SetTitle("Test Dialog");
    EXPECT_STREQ(dialog.GetTitle(), "Test Dialog");
}

TEST(CDialogTest, ShowHide) {
    CDialog dialog;
    dialog.Show();
    EXPECT_TRUE(dialog.IsVisible());
    dialog.Hide();
    EXPECT_FALSE(dialog.IsVisible());
}
