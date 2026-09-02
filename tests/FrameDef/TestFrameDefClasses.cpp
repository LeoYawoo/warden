#include <gtest/gtest.h>
#include "FrameDef/IFrameDef.h"
#include "FrameDef/FrameDef.h"
#include "FrameDef/SetupFrame.h"

// Test IFrameDef (abstract interface - test via FrameDef)

// Test FrameDef
TEST(FrameDefTest, DefaultConstructor) {
    FrameDef fd;
    EXPECT_EQ(fd.GetFrameId(), 0);
    EXPECT_TRUE(fd.IsEnabled());
    EXPECT_EQ(fd.GetParent(), nullptr);
    EXPECT_EQ(fd.GetChild(), nullptr);
    EXPECT_EQ(fd.GetNext(), nullptr);
}

TEST(FrameDefTest, SetName) {
    FrameDef fd;
    fd.SetName("TestFrame");
    EXPECT_STREQ(fd.GetName(), "TestFrame");
}

TEST(FrameDefTest, SetType) {
    FrameDef fd;
    fd.SetType(3);
    EXPECT_EQ(fd.GetType(), 3);
}

TEST(FrameDefTest, SetEnabled) {
    FrameDef fd;
    fd.SetEnabled(false);
    EXPECT_FALSE(fd.IsEnabled());
}

TEST(FrameDefTest, SetFrameId) {
    FrameDef fd;
    fd.SetFrameId(42);
    EXPECT_EQ(fd.GetFrameId(), 42);
}

TEST(FrameDefTest, SetParentName) {
    FrameDef fd;
    fd.SetParentName("ParentFrame");
    EXPECT_STREQ(fd.GetParentName(), "ParentFrame");
}

TEST(FrameDefTest, SetParentChildNext) {
    FrameDef parent;
    FrameDef child;
    FrameDef next;

    child.SetParent(&parent);
    parent.SetChild(&child);
    child.SetNext(&next);

    EXPECT_EQ(child.GetParent(), &parent);
    EXPECT_EQ(parent.GetChild(), &child);
    EXPECT_EQ(child.GetNext(), &next);
}

TEST(FrameDefTest, CreateFrame) {
    FrameDef fd;
    // CreateFrame returns nullptr in stub implementation
    EXPECT_EQ(fd.CreateFrame(), nullptr);
}

// Test SetupFrame
TEST(SetupFrameTest, DefaultConstructor) {
    SetupFrame sf;
    EXPECT_EQ(sf.GetSetupId(), 0);
    EXPECT_FALSE(sf.IsComplete());
}

TEST(SetupFrameTest, SetSetupId) {
    SetupFrame sf;
    sf.SetSetupId(10);
    EXPECT_EQ(sf.GetSetupId(), 10);
}

TEST(SetupFrameTest, SetSetupName) {
    SetupFrame sf;
    sf.SetSetupName("TestSetup");
    EXPECT_STREQ(sf.GetSetupName(), "TestSetup");
}

TEST(SetupFrameTest, SetComplete) {
    SetupFrame sf;
    sf.SetComplete(true);
    EXPECT_TRUE(sf.IsComplete());
}

TEST(SetupFrameTest, Setup) {
    SetupFrame sf;
    FrameDef fd;
    EXPECT_TRUE(sf.Setup(&fd));
    EXPECT_TRUE(sf.IsComplete());
}

TEST(SetupFrameTest, Reset) {
    SetupFrame sf;
    FrameDef fd;
    sf.Setup(&fd);
    sf.Reset();
    EXPECT_FALSE(sf.IsComplete());
}

TEST(SetupFrameTest, SetupWithNull) {
    SetupFrame sf;
    EXPECT_FALSE(sf.Setup(nullptr));
}
