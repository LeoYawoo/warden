#include <gtest/gtest.h>
#include "Event/EvtHandler.h"

// Test handler function
static int32_t TestHandler(const void* data, void* param) {
    return *static_cast<int*>(param);
}

// Another test handler function
static int32_t TestHandler2(const void* data, void* param) {
    return *static_cast<int*>(param) * 2;
}

TEST(EvtHandlerTest, DefaultConstructor) {
    EvtHandler handler;
    EXPECT_FALSE(handler.IsValid());
    EXPECT_EQ(handler.func, nullptr);
    EXPECT_EQ(handler.param, nullptr);
    EXPECT_FLOAT_EQ(handler.priority, 0.0f);
    EXPECT_EQ(handler.marker, 0);
}

TEST(EvtHandlerTest, ParameterizedConstructor) {
    int param = 42;
    EvtHandler handler(TestHandler, &param, 1.0f);

    EXPECT_TRUE(handler.IsValid());
    EXPECT_EQ(handler.func, TestHandler);
    EXPECT_EQ(handler.param, &param);
    EXPECT_FLOAT_EQ(handler.priority, 1.0f);
}

TEST(EvtHandlerTest, Invoke) {
    int param = 42;
    EvtHandler handler(TestHandler, &param);

    int result = handler.Invoke(nullptr);
    EXPECT_EQ(result, 42);
}

TEST(EvtHandlerTest, InvokeWithDifferentHandler) {
    int param = 10;
    EvtHandler handler(TestHandler2, &param);

    int result = handler.Invoke(nullptr);
    EXPECT_EQ(result, 20);
}

TEST(EvtHandlerTest, InvokeNullHandler) {
    EvtHandler handler;
    int result = handler.Invoke(nullptr);
    EXPECT_EQ(result, 0);
}

TEST(EvtHandlerTest, Equality) {
    int param = 42;
    EvtHandler handler1(TestHandler, &param);
    EvtHandler handler2(TestHandler, &param);
    EvtHandler handler3(TestHandler2, &param);

    EXPECT_TRUE(handler1 == handler2);
    EXPECT_FALSE(handler1 == handler3);
}

TEST(EvtHandlerTest, Inequality) {
    int param = 42;
    EvtHandler handler1(TestHandler, &param);
    EvtHandler handler2(TestHandler2, &param);

    EXPECT_TRUE(handler1 != handler2);
}

TEST(EvtHandlerTest, PriorityComparison) {
    int param = 42;
    EvtHandler handler1(TestHandler, &param, 1.0f);
    EvtHandler handler2(TestHandler, &param, 2.0f);

    EXPECT_TRUE(handler1 < handler2);
    EXPECT_TRUE(handler2 > handler1);
}

TEST(EvtHandlerTest, IsValidWithNullFunction) {
    EvtHandler handler;
    handler.func = TestHandler;
    handler.param = nullptr;

    EXPECT_TRUE(handler.IsValid());
}

TEST(EvtHandlerTest, IsValidWithNullParam) {
    int param = 42;
    EvtHandler handler(TestHandler, &param);
    handler.param = nullptr;

    EXPECT_TRUE(handler.IsValid());
}
