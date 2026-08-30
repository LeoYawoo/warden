#include <gtest/gtest.h>
#include "Event/EvtTimer.h"

// Test timer handler function
static int32_t TestTimerHandler(const void* data, void* param) {
    return *static_cast<int*>(param);
}

TEST(EvtTimerTest, DefaultConstructor) {
    EvtTimer timer;
    EXPECT_EQ(timer.id, 0u);
    EXPECT_FLOAT_EQ(timer.timeout, 0.0f);
    EXPECT_EQ(timer.handler, nullptr);
    EXPECT_EQ(timer.param, nullptr);
    EXPECT_FALSE(timer.IsValid());
}

TEST(EvtTimerTest, ParameterizedConstructor) {
    int param = 42;
    EvtTimer timer(1, 5.0f, TestTimerHandler, &param);

    EXPECT_EQ(timer.id, 1u);
    EXPECT_FLOAT_EQ(timer.timeout, 5.0f);
    EXPECT_EQ(timer.handler, TestTimerHandler);
    EXPECT_EQ(timer.param, &param);
    EXPECT_TRUE(timer.IsValid());
}

TEST(EvtTimerTest, SetTimeout) {
    EvtTimer timer;
    timer.SetTimeout(2.0f, 1000);

    EXPECT_FLOAT_EQ(timer.timeout, 2.0f);
    EXPECT_EQ(timer.targetTime.m_val, 3000u);
}

TEST(EvtTimerTest, HasExpired) {
    EvtTimer timer;
    timer.SetTimeout(1.0f, 1000);

    EXPECT_FALSE(timer.HasExpired(1500));
    EXPECT_TRUE(timer.HasExpired(2000));
    EXPECT_TRUE(timer.HasExpired(3000));
}

TEST(EvtTimerTest, Equality) {
    EvtTimer timer1(1, 5.0f, TestTimerHandler, nullptr);
    EvtTimer timer2(1, 10.0f, TestTimerHandler, nullptr);
    EvtTimer timer3(2, 5.0f, TestTimerHandler, nullptr);

    EXPECT_TRUE(timer1 == timer2);
    EXPECT_FALSE(timer1 == timer3);
}

TEST(EvtTimerTest, Inequality) {
    EvtTimer timer1(1, 5.0f, TestTimerHandler, nullptr);
    EvtTimer timer2(2, 5.0f, TestTimerHandler, nullptr);

    EXPECT_TRUE(timer1 != timer2);
}

TEST(EvtTimerTest, PriorityComparison) {
    EvtTimer timer1;
    timer1.targetTime.m_val = 1000;

    EvtTimer timer2;
    timer2.targetTime.m_val = 2000;

    EXPECT_TRUE(timer1 < timer2);
    EXPECT_TRUE(timer2 > timer1);
}

TEST(EvtTimerTest, IsValidWithGuidHandler) {
    EvtTimer timer;
    timer.guidHandler = [](const void*, uint64_t, void*) -> int32_t { return 0; };

    EXPECT_TRUE(timer.IsValid());
}

TEST(EvtTimerTest, InvalidTimer) {
    EvtTimer timer;
    EXPECT_FALSE(timer.IsValid());

    timer.handler = TestTimerHandler;
    EXPECT_TRUE(timer.IsValid());

    timer.handler = nullptr;
    EXPECT_FALSE(timer.IsValid());
}
