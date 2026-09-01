#include <gtest/gtest.h>
#include "StormMac/big/BigBuffer.h"
#include "StormMac/big/BigStack.h"
#include "StormMac/big/BigData.h"

// Test BigBuffer
TEST(BigBufferTest, DefaultConstructor) {
    BigBuffer buffer;
    EXPECT_EQ(buffer.Count(), 0u);
}

TEST(BigBufferTest, SetCount) {
    BigBuffer buffer;
    buffer.SetCount(10);
    EXPECT_EQ(buffer.Count(), 10u);
}

TEST(BigBufferTest, OperatorIndex) {
    BigBuffer buffer;
    buffer.SetCount(5);
    buffer[0] = 100;
    EXPECT_EQ(buffer[0], 100u);
}

TEST(BigBufferTest, GrowToFit) {
    BigBuffer buffer;
    buffer.GrowToFit(10);
    EXPECT_GE(buffer.Count(), 11u);
}

TEST(BigBufferTest, IsUsed) {
    BigBuffer buffer;
    buffer.SetCount(5);
    buffer[0] = 100;
    EXPECT_TRUE(buffer.IsUsed(0));
    EXPECT_FALSE(buffer.IsUsed(1));
}

TEST(BigBufferTest, Clear) {
    BigBuffer buffer;
    buffer.SetCount(10);
    buffer.Clear();
    EXPECT_EQ(buffer.Count(), 0u);
}

TEST(BigBufferTest, SetOffset) {
    BigBuffer buffer;
    buffer.SetOffset(42);
    EXPECT_EQ(buffer.m_offset, 42u);
}

// Test BigStack
TEST(BigStackTest, DefaultConstructor) {
    BigStack stack;
    EXPECT_EQ(stack.m_used, 0u);
}

TEST(BigStackTest, Alloc) {
    BigStack stack;
    uint32_t count = 0;
    BigBuffer &buf = stack.Alloc(&count);
    EXPECT_EQ(stack.m_used, 1u);
    (void)buf;
}

TEST(BigStackTest, AllocMultiple) {
    BigStack stack;
    uint32_t count = 0;
    stack.Alloc(&count);
    stack.Alloc(&count);
    stack.Alloc(&count);
    EXPECT_EQ(stack.m_used, 3u);
}

TEST(BigStackTest, Free) {
    BigStack stack;
    uint32_t count = 0;
    stack.Alloc(&count);
    stack.Alloc(&count);
    stack.Free(count);
    EXPECT_EQ(stack.m_used, 1u);
}

// Test BigData
TEST(BigDataTest, DefaultConstructor) {
    BigData data;
    EXPECT_EQ(data.Primary().Count(), 0u);
}

TEST(BigDataTest, Primary) {
    BigData data;
    BigBuffer &primary = data.Primary();
    primary.SetCount(10);
    EXPECT_EQ(data.Primary().Count(), 10u);
}

TEST(BigDataTest, Stack) {
    BigData data;
    BigStack &stack = data.Stack();
    uint32_t count = 0;
    stack.Alloc(&count);
    EXPECT_EQ(data.Stack().m_used, 1u);
}

TEST(BigDataTest, Output) {
    BigData data;
    TSGrowableArray<uint8_t> &output = data.Output();
    (void)output;
    // Verify output is accessible
}
