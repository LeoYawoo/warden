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
}

TEST(TSLinkTest, IsLinked) {
    TestNode node(42);
    EXPECT_FALSE(node.m_link.IsLinked());
}

TEST(TSLinkTest, UnlinkWhenNotLinked) {
    TestNode node(42);
    node.m_link.Unlink();
    EXPECT_FALSE(node.m_link.IsLinked());
}

TEST(TSLinkTest, RawNext) {
    TestNode node1(1);
    TestNode node2(2);

    node1.m_link.m_next = &node2;
    node2.m_link.m_prevlink = &node1.m_link;

    EXPECT_EQ(node1.m_link.RawNext(), &node2);
}

TEST(TSLinkTest, NextWithSentinel) {
    TestNode node(42);

    node.m_link.m_next = reinterpret_cast<TestNode *>(~reinterpret_cast<uintptr_t>(&node.m_link));

    EXPECT_EQ(node.m_link.Next(), nullptr);
}

TEST(TSLinkTest, ManualLinking) {
    TestNode node1(1);
    TestNode node2(2);
    TestNode node3(3);

    // Manually link: node1 -> node2 -> node3
    node1.m_link.m_next = &node2;
    node2.m_link.m_prevlink = &node1.m_link;
    node2.m_link.m_next = &node3;
    node3.m_link.m_prevlink = &node2.m_link;

    EXPECT_EQ(node1.m_link.Next(), &node2);
    EXPECT_EQ(node2.m_link.Next(), &node3);
    EXPECT_EQ(node3.m_link.Next(), nullptr);
}

TEST(TSLinkTest, UnlinkFromChain) {
    TestNode node1(1);
    TestNode node2(2);
    TestNode node3(3);

    // Manually link: node1 -> node2 -> node3
    node1.m_link.m_next = &node2;
    node2.m_link.m_prevlink = &node1.m_link;
    node2.m_link.m_next = &node3;
    node3.m_link.m_prevlink = &node2.m_link;

    // Unlink node2
    node2.m_link.Unlink();

    EXPECT_EQ(node1.m_link.m_next, &node3);
    EXPECT_FALSE(node2.m_link.IsLinked());
}
