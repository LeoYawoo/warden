#include <gtest/gtest.h>
#include "Ipse/CRlAgent.h"

TEST(CRlAgentTest, DefaultConstructor) {
    Ipse::CRlAgent agent;
    EXPECT_EQ(agent.GetId(), 0u);
    EXPECT_EQ(agent.GetName(), "");
    EXPECT_FALSE(agent.IsActive());
    EXPECT_FLOAT_EQ(agent.GetLearningRate(), 0.01f);
    EXPECT_FLOAT_EQ(agent.GetDiscountFactor(), 0.99f);
    EXPECT_FLOAT_EQ(agent.GetExplorationRate(), 0.1f);
}

TEST(CRlAgentTest, ParameterizedConstructor) {
    Ipse::CRlAgent agent(42, "TestAgent");
    EXPECT_EQ(agent.GetId(), 42u);
    EXPECT_EQ(agent.GetName(), "TestAgent");
    EXPECT_FALSE(agent.IsActive());
}

TEST(CRlAgentTest, SetId) {
    Ipse::CRlAgent agent;
    agent.SetId(100);
    EXPECT_EQ(agent.GetId(), 100u);
}

TEST(CRlAgentTest, SetName) {
    Ipse::CRlAgent agent;
    agent.SetName("NewName");
    EXPECT_EQ(agent.GetName(), "NewName");
}

TEST(CRlAgentTest, SetActive) {
    Ipse::CRlAgent agent;
    agent.SetActive(true);
    EXPECT_TRUE(agent.IsActive());
    agent.SetActive(false);
    EXPECT_FALSE(agent.IsActive());
}

TEST(CRlAgentTest, SetLearningRate) {
    Ipse::CRlAgent agent;
    agent.SetLearningRate(0.05f);
    EXPECT_FLOAT_EQ(agent.GetLearningRate(), 0.05f);
}

TEST(CRlAgentTest, SetDiscountFactor) {
    Ipse::CRlAgent agent;
    agent.SetDiscountFactor(0.95f);
    EXPECT_FLOAT_EQ(agent.GetDiscountFactor(), 0.95f);
}

TEST(CRlAgentTest, SetExplorationRate) {
    Ipse::CRlAgent agent;
    agent.SetExplorationRate(0.2f);
    EXPECT_FLOAT_EQ(agent.GetExplorationRate(), 0.2f);
}

TEST(CRlAgentTest, Initialize) {
    Ipse::CRlAgent agent;
    agent.Initialize();
    EXPECT_TRUE(agent.IsActive());
}

TEST(CRlAgentTest, Shutdown) {
    Ipse::CRlAgent agent;
    agent.Initialize();
    agent.Shutdown();
    EXPECT_FALSE(agent.IsActive());
}

TEST(CRlAgentTest, Reset) {
    Ipse::CRlAgent agent(42, "TestAgent");
    agent.Initialize();
    agent.SetLearningRate(0.05f);
    agent.SetDiscountFactor(0.95f);
    agent.SetExplorationRate(0.2f);

    agent.Reset();

    EXPECT_FALSE(agent.IsActive());
    EXPECT_FLOAT_EQ(agent.GetLearningRate(), 0.01f);
    EXPECT_FLOAT_EQ(agent.GetDiscountFactor(), 0.99f);
    EXPECT_FLOAT_EQ(agent.GetExplorationRate(), 0.1f);
}

TEST(CRlAgentTest, ShouldExplore) {
    Ipse::CRlAgent agent;
    agent.SetExplorationRate(0.0f);
    // With 0% exploration rate, should never explore
    for (int i = 0; i < 100; ++i) {
        EXPECT_FALSE(agent.ShouldExplore());
    }

    agent.SetExplorationRate(1.0f);
    // With 100% exploration rate, should always explore
    for (int i = 0; i < 100; ++i) {
        EXPECT_TRUE(agent.ShouldExplore());
    }
}

TEST(CRlAgentTest, VirtualFunctions) {
    Ipse::CRlAgent agent;
    // These should not crash
    agent.Initialize();
    agent.Shutdown();
    agent.Update(1.0f);
}
