#include <gtest/gtest.h>
#include "NIpse/CRlAgent.h"

TEST(CRlAgentTest, DefaultConstructor) {
    NIpse::CRlAgent agent;
    EXPECT_EQ(agent.GetId(), 0u);
    EXPECT_EQ(agent.GetName(), "");
    EXPECT_FALSE(agent.IsActive());
    EXPECT_FLOAT_EQ(agent.GetLearningRate(), 0.01f);
    EXPECT_FLOAT_EQ(agent.GetDiscountFactor(), 0.99f);
    EXPECT_FLOAT_EQ(agent.GetExplorationRate(), 0.1f);
}

TEST(CRlAgentTest, ParameterizedConstructor) {
    NIpse::CRlAgent agent(42, "TestAgent");
    EXPECT_EQ(agent.GetId(), 42u);
    EXPECT_EQ(agent.GetName(), "TestAgent");
    EXPECT_FALSE(agent.IsActive());
}

TEST(CRlAgentTest, SetId) {
    NIpse::CRlAgent agent;
    agent.SetId(100);
    EXPECT_EQ(agent.GetId(), 100u);
}

TEST(CRlAgentTest, SetName) {
    NIpse::CRlAgent agent;
    agent.SetName("NewName");
    EXPECT_EQ(agent.GetName(), "NewName");
}

TEST(CRlAgentTest, SetActive) {
    NIpse::CRlAgent agent;
    agent.SetActive(true);
    EXPECT_TRUE(agent.IsActive());
    agent.SetActive(false);
    EXPECT_FALSE(agent.IsActive());
}

TEST(CRlAgentTest, SetLearningRate) {
    NIpse::CRlAgent agent;
    agent.SetLearningRate(0.05f);
    EXPECT_FLOAT_EQ(agent.GetLearningRate(), 0.05f);
}

TEST(CRlAgentTest, SetDiscountFactor) {
    NIpse::CRlAgent agent;
    agent.SetDiscountFactor(0.95f);
    EXPECT_FLOAT_EQ(agent.GetDiscountFactor(), 0.95f);
}

TEST(CRlAgentTest, SetExplorationRate) {
    NIpse::CRlAgent agent;
    agent.SetExplorationRate(0.2f);
    EXPECT_FLOAT_EQ(agent.GetExplorationRate(), 0.2f);
}

TEST(CRlAgentTest, Initialize) {
    NIpse::CRlAgent agent;
    agent.Initialize();
    EXPECT_TRUE(agent.IsActive());
}

TEST(CRlAgentTest, Shutdown) {
    NIpse::CRlAgent agent;
    agent.Initialize();
    agent.Shutdown();
    EXPECT_FALSE(agent.IsActive());
}

TEST(CRlAgentTest, Reset) {
    NIpse::CRlAgent agent(42, "TestAgent");
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
    NIpse::CRlAgent agent;
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
    NIpse::CRlAgent agent;
    // These should not crash
    agent.Initialize();
    agent.Shutdown();
    agent.Update(1.0f);
}
