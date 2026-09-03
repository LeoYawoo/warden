#include <gtest/gtest.h>
#include "Ipse/CRlAgent.h"

TEST(CRlAgentTest, DefaultConstructor) {
    NIpse::CRlAgent agent;
    EXPECT_EQ(agent.GetAgentId(), 0);
    EXPECT_FALSE(agent.IsInitialized());
    EXPECT_FALSE(agent.IsRunning());
}

TEST(CRlAgentTest, SetAgentId) {
    NIpse::CRlAgent agent;
    agent.SetAgentId(100);
    EXPECT_EQ(agent.GetAgentId(), 100);
}

TEST(CRlAgentTest, SetAgentName) {
    NIpse::CRlAgent agent;
    agent.SetAgentName("TestAgent");
    EXPECT_STREQ(agent.GetAgentName(), "TestAgent");
}

TEST(CRlAgentTest, Initialize) {
    NIpse::CRlAgent agent;
    agent.Initialize();
    EXPECT_TRUE(agent.IsInitialized());
}

TEST(CRlAgentTest, Shutdown) {
    NIpse::CRlAgent agent;
    agent.Initialize();
    agent.SetRunning(true);
    agent.Shutdown();
    EXPECT_FALSE(agent.IsRunning());
    EXPECT_FALSE(agent.IsInitialized());
}

TEST(CRlAgentTest, VirtualFunctions) {
    NIpse::CRlAgent agent;
    agent.Initialize();
    agent.Shutdown();
    agent.Update(1.0f);
}
