#include <gtest/gtest.h>
#include "StormMac/xml/XMLNode.h"
#include "StormMac/xml/XMLTree.h"
#include "StormMac/mempool/MemPool.h"
#include "StormMac/mempool/MemChunk.h"

// Test XMLNode
TEST(XMLNodeTest, DefaultConstructor) {
    XMLNode node;
    EXPECT_EQ(node.m_parent, nullptr);
    EXPECT_EQ(node.m_child, nullptr);
    EXPECT_EQ(node.m_next, nullptr);
    EXPECT_EQ(node.m_body, nullptr);
}

TEST(XMLNodeTest, GetName) {
    XMLNode node;
    node.Init(nullptr, "test");
    EXPECT_STREQ(node.GetName(), "test");
}

TEST(XMLNodeTest, GetBody) {
    XMLNode node;
    EXPECT_EQ(node.GetBody(), nullptr);
}

TEST(XMLNodeTest, SetAttribute) {
    XMLNode node;
    node.SetAttribute("name", "value");
    EXPECT_STREQ(node.GetAttributeByName("name"), "value");
}

TEST(XMLNodeTest, GetAttributeNotFound) {
    XMLNode node;
    EXPECT_EQ(node.GetAttributeByName("nonexistent"), nullptr);
}

TEST(XMLNodeTest, InitWithParent) {
    XMLNode parent;
    XMLNode child;
    child.Init(&parent, "child");

    EXPECT_EQ(child.m_parent, &parent);
    EXPECT_EQ(parent.m_child, &child);
}

TEST(XMLNodeTest, GetChildByName) {
    XMLNode parent;
    XMLNode child1;
    XMLNode child2;

    child1.Init(&parent, "child1");
    child2.Init(&parent, "child2");

    EXPECT_EQ(parent.GetChildByName("child1"), &child1);
    EXPECT_EQ(parent.GetChildByName("child2"), &child2);
    EXPECT_EQ(parent.GetChildByName("nonexistent"), nullptr);
}

// Test XMLTree
TEST(XMLTreeTest, GetRootNull) {
    EXPECT_EQ(XMLTree_GetRoot(nullptr), nullptr);
}

TEST(XMLTreeTest, LoadNull) {
    EXPECT_EQ(XMLTree_Load(nullptr, 0), nullptr);
}

TEST(XMLTreeTest, LoadEmpty) {
    EXPECT_EQ(XMLTree_Load("", 0), nullptr);
}

TEST(XMLTreeTest, LoadSimple) {
    const char* xml = "<root><child>text</child></root>";
    XMLTree* tree = XMLTree_Load(xml, strlen(xml));
    EXPECT_NE(tree, nullptr);
    EXPECT_NE(XMLTree_GetRoot(tree), nullptr);
    XMLTree_Free(tree);
}

// Test MemChunk
TEST(MemChunkTest, Constructor) {
    MemChunk chunk(64, 10);
    EXPECT_NE(chunk.m_memblocks, nullptr);
}

TEST(MemChunkTest, Contains) {
    MemChunk chunk(64, 10);
    void* ptr = chunk.MemAlloc();
    EXPECT_NE(ptr, nullptr);
    EXPECT_TRUE(chunk.Contains(ptr));
}

TEST(MemChunkTest, MemAllocFree) {
    MemChunk chunk(64, 10);
    void* ptr1 = chunk.MemAlloc();
    void* ptr2 = chunk.MemAlloc();

    EXPECT_NE(ptr1, nullptr);
    EXPECT_NE(ptr2, nullptr);
    EXPECT_NE(ptr1, ptr2);

    chunk.MemFree(ptr1);
    chunk.MemFree(ptr2);
}

// Test MemPool
TEST(MemPoolTest, DefaultConstructor) {
    MemPool pool;
    EXPECT_EQ(pool.m_blockSize, 0u);
}

TEST(MemPoolTest, Init) {
    MemPool pool;
    pool.Init(64, 10);
    EXPECT_EQ(pool.m_blockSize, 64u);
}

TEST(MemPoolTest, MemAlloc) {
    MemPool pool;
    pool.Init(64, 10);
    void* ptr = pool.MemAlloc();
    EXPECT_NE(ptr, nullptr);
}

TEST(MemPoolTest, MemAllocMultiple) {
    MemPool pool;
    pool.Init(64, 10);
    void* ptr1 = pool.MemAlloc();
    void* ptr2 = pool.MemAlloc();
    void* ptr3 = pool.MemAlloc();

    EXPECT_NE(ptr1, nullptr);
    EXPECT_NE(ptr2, nullptr);
    EXPECT_NE(ptr3, nullptr);
}

TEST(MemPoolTest, MemFree) {
    MemPool pool;
    pool.Init(64, 10);
    void* ptr = pool.MemAlloc();
    EXPECT_TRUE(pool.MemFree(ptr));
}

TEST(MemPoolTest, MemFreeNull) {
    MemPool pool;
    EXPECT_FALSE(pool.MemFree(nullptr));
}
