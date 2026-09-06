#include <gtest/gtest.h>
#include "FDFile/FDFile.h"
#include "FDFile/Handlers/FrameHashNode.h"
#include "FDFile/Handlers/MenuHashNode.h"

// Test FrameHashNode
TEST(FrameHashNodeTest, DefaultConstructor) {
    FrameHashNode node;
    EXPECT_EQ(node.GetNodeId(), 0);
    EXPECT_FALSE(node.IsValid());
    EXPECT_EQ(node.GetNext(), nullptr);
}

TEST(FrameHashNodeTest, SetName) {
    FrameHashNode node;
    node.SetName("TestFrame");
    EXPECT_STREQ(node.GetName(), "TestFrame");
}

TEST(FrameHashNodeTest, SetNodeId) {
    FrameHashNode node;
    node.SetNodeId(42);
    EXPECT_EQ(node.GetNodeId(), 42);
}

TEST(FrameHashNodeTest, SetFrameDef) {
    FrameHashNode node;
    FdfNode frameDef;
    node.SetFrameDef(&frameDef);
    EXPECT_TRUE(node.IsValid());
    EXPECT_EQ(node.GetFrameDef(), &frameDef);
}

TEST(FrameHashNodeTest, SetNext) {
    FrameHashNode node1;
    FrameHashNode node2;
    node1.SetNext(&node2);
    EXPECT_EQ(node1.GetNext(), &node2);
}

TEST(FrameHashNodeTest, Clear) {
    FrameHashNode node;
    FdfNode frameDef;
    node.SetFrameDef(&frameDef);
    node.Clear();
    EXPECT_FALSE(node.IsValid());
}

// Test MenuHashNode
TEST(MenuHashNodeTest, DefaultConstructor) {
    MenuHashNode node;
    EXPECT_EQ(node.GetNodeId(), 0);
    EXPECT_TRUE(node.IsEnabled());
    EXPECT_EQ(node.GetMenuId(), 0);
}

TEST(MenuHashNodeTest, SetName) {
    MenuHashNode node;
    node.SetName("TestMenu");
    EXPECT_STREQ(node.GetName(), "TestMenu");
}

TEST(MenuHashNodeTest, SetNodeId) {
    MenuHashNode node;
    node.SetNodeId(10);
    EXPECT_EQ(node.GetNodeId(), 10);
}

TEST(MenuHashNodeTest, SetEnabled) {
    MenuHashNode node;
    node.SetEnabled(false);
    EXPECT_FALSE(node.IsEnabled());
}

TEST(MenuHashNodeTest, SetMenuText) {
    MenuHashNode node;
    node.SetMenuText("File Menu");
    EXPECT_STREQ(node.GetMenuText(), "File Menu");
}

TEST(MenuHashNodeTest, SetMenuId) {
    MenuHashNode node;
    node.SetMenuId(100);
    EXPECT_EQ(node.GetMenuId(), 100);
}

TEST(MenuHashNodeTest, IsValid) {
    MenuHashNode node;
    EXPECT_FALSE(node.IsValid());
    node.SetName("TestMenu");
    EXPECT_TRUE(node.IsValid());
}

TEST(MenuHashNodeTest, Clear) {
    MenuHashNode node;
    node.SetName("TestMenu");
    node.SetMenuText("File Menu");
    node.Clear();
    EXPECT_FALSE(node.IsValid());
    EXPECT_STREQ(node.GetMenuText(), "");
}

// Test FDFile handler integration
TEST(FDFileHandlerTest, DefaultConstructor) {
    FDFile fd;
    EXPECT_FALSE(fd.IsValid());
    EXPECT_EQ(fd.GetStatus(), FRAMEDEF_STATUS_OK);
}

TEST(FDFileHandlerTest, ParseFDF) {
    FDFile fd;
    const char* fdf = R"(
Frame "FRAME" "TestFrame" {
    Width 0.5,
}
)";
    EXPECT_TRUE(fd.LoadFromMemory(fdf, strlen(fdf)));
    EXPECT_TRUE(fd.IsValid());
}

TEST(FDFileHandlerTest, Clear) {
    FDFile fd;
    const char* fdf = R"(
Frame "FRAME" "TestFrame" {
    Width 0.5,
}
)";
    fd.LoadFromMemory(fdf, strlen(fdf));
    fd.Clear();
    EXPECT_FALSE(fd.IsValid());
}
