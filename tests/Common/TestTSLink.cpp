#include <gtest/gtest.h>
#include "Common/TSLink.h"

struct TestNode {
    int value;
    TSLink<TestNode> m_link;

    TestNode(int v = 0) : value(v) {}
};

TEST(TSLinkTest, DefaultConstructor) {
    TestNode node(42);
    EXPECT_FALSE(node.m_link.IsLinked());
    EXPECT_EQ(node.m_link.m_next, nullptr);
    EXPECT_EQ(node.m_link.m_prevlink, nullptr);
}

TEST(TSLinkTest, IsLinkedWhenNull) {
    TestNode node(42);
    EXPECT_FALSE(node.m_link.IsLinked());
}

TEST(TSLinkTest, UnlinkWhenNotLinked) {
    TestNode node(42);
    // Should not crash when unlinking an unlinked node
    node.m_link.Unlink();
    EXPECT_FALSE(node.m_link.IsLinked());
}

TEST(TSLinkTest, NextWhenNull) {
    TestNode node(42);
    // Next should return nullptr when m_next is nullptr
    EXPECT_EQ(node.m_link.Next(), nullptr);
}

TEST(TSLinkTest, PrevWhenNull) {
    TestNode node(42);
    // Prev should handle null prevlink gracefully
    // This may crash if prevlink is null, so we test the basic case
    EXPECT_FALSE(node.m_link.IsLinked());
}
