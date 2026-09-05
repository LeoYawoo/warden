#include <gtest/gtest.h>
#include "Agile/CUnitRefList.h"
#include "Source/CAgentWar3.h"
#include "Agile/AgentRefMini.h"
#include "Agile/AgentRef.h"
#include "Agile/CEvent.h"
#include "Agile/CListenerEvent.h"

// Test CUnitRefList
TEST(CUnitRefListTest, DefaultConstructor) {
    CUnitRefList list;
    EXPECT_EQ(list.GetUnit(), nullptr);
    EXPECT_EQ(list.GetNext(), nullptr);
}

TEST(CUnitRefListTest, Initialize) {
    CUnitRefList list;
    CUnitRefList nextList;
    list.Initialize(nullptr, &nextList);
    EXPECT_EQ(list.GetNext(), &nextList);
}

// Test CAgentWar3
TEST(CAgentWar3Test, DefaultConstructor) {
    CAgentWar3 agent;
    EXPECT_EQ(agent.GetUnit(), nullptr);
    EXPECT_FALSE(agent.IsValid());
    EXPECT_EQ(agent.GetAgentId(), 0);
}

TEST(CAgentWar3Test, SetUnit) {
    CAgentWar3 agent;
    // CUnit is forward declared, use nullptr for test
    agent.SetUnit(nullptr);
    EXPECT_EQ(agent.GetUnit(), nullptr);
}

// Test AgentRefMini
TEST(AgentRefMiniTest, DefaultConstructor) {
    AgentRefMini ref;
    EXPECT_FALSE(ref.IsAssigned());
    EXPECT_EQ(ref.GetAgent(), nullptr);
}

TEST(AgentRefMiniTest, Assignment) {
    AgentRefMini ref;
    CAgent agent;
    ref = &agent;
    EXPECT_TRUE(ref.IsAssigned());
    EXPECT_EQ(ref.GetAgent(), &agent);
}

TEST(AgentRefMiniTest, SameAgent) {
    AgentRefMini ref;
    CAgent agent1;
    CAgent agent2;

    ref = &agent1;
    EXPECT_TRUE(ref.SameAgent(&agent1));
    EXPECT_FALSE(ref.SameAgent(&agent2));
}

// Test AgentRef
TEST(AgentRefTest, DefaultConstructor) {
    AgentRef ref;
    EXPECT_FALSE(ref.IsValid());
    EXPECT_EQ(ref.GetAgent(), nullptr);
}

TEST(AgentRefTest, SetAgent) {
    AgentRef ref;
    CAgent agent;
    ref.SetAgent(&agent);
    EXPECT_TRUE(ref.IsValid());
    EXPECT_EQ(ref.GetAgent(), &agent);
}

TEST(AgentRefTest, Clear) {
    AgentRef ref;
    CAgent agent;
    ref.SetAgent(&agent);
    EXPECT_TRUE(ref.IsValid());

    ref.Clear();
    EXPECT_FALSE(ref.IsValid());
    EXPECT_EQ(ref.GetAgent(), nullptr);
}

// Test CEvent
TEST(CEventTest, DefaultConstructor) {
    CEvent event;
    EXPECT_FALSE(event.IsValid());
    EXPECT_EQ(event.GetEventData(), nullptr);
}

TEST(CEventTest, ParameterizedConstructor) {
    int data = 42;
    CEvent event(100, &data);
    EXPECT_TRUE(event.IsValid());
    EXPECT_EQ(event.GetEventType(), 100u);
    EXPECT_EQ(event.GetEventData(), &data);
}

TEST(CEventTest, CopyConstructor) {
    int data = 42;
    CEvent event1(100, &data);
    CEvent event2(event1);
    EXPECT_TRUE(event2.IsValid());
    EXPECT_EQ(event2.GetEventType(), 100u);
    EXPECT_EQ(event2.GetEventData(), &data);
}

TEST(CEventTest, SetEventData) {
    CEvent event(100, nullptr);
    int data = 42;
    event.SetEventData(&data);
    EXPECT_EQ(event.GetEventData(), &data);
}

// Test CListenerEvent
TEST(CListenerEventTest, DefaultConstructor) {
    CListenerEvent event;
    EXPECT_FALSE(event.IsValid());
    EXPECT_EQ(event.GetListener(), nullptr);
}

TEST(CListenerEventTest, SetListener) {
    CListenerEvent event;
    int listener = 42;
    event.SetListener(&listener);
    EXPECT_EQ(event.GetListener(), &listener);
}
