#include <gtest/gtest.h>
#include "NIpse/CRlAgentDef.h"

TEST(CRlAgentDefTest, DefaultConstructor) {
    NIpse::CRlAgentDef def;
    EXPECT_EQ(def.GetId(), 0u);
    EXPECT_EQ(def.GetName(), "");
    EXPECT_EQ(def.GetDescription(), "");
    EXPECT_FLOAT_EQ(def.GetDefaultLearningRate(), 0.01f);
    EXPECT_FLOAT_EQ(def.GetDefaultDiscountFactor(), 0.99f);
    EXPECT_FLOAT_EQ(def.GetDefaultExplorationRate(), 0.1f);
    EXPECT_EQ(def.GetMaxEpisodes(), 1000u);
    EXPECT_EQ(def.GetMaxStepsPerEpisode(), 100u);
}

TEST(CRlAgentDefTest, ParameterizedConstructor) {
    NIpse::CRlAgentDef def(42, "TestDef");
    EXPECT_EQ(def.GetId(), 42u);
    EXPECT_EQ(def.GetName(), "TestDef");
}

TEST(CRlAgentDefTest, SetId) {
    NIpse::CRlAgentDef def;
    def.SetId(100);
    EXPECT_EQ(def.GetId(), 100u);
}

TEST(CRlAgentDefTest, SetName) {
    NIpse::CRlAgentDef def;
    def.SetName("NewName");
    EXPECT_EQ(def.GetName(), "NewName");
}

TEST(CRlAgentDefTest, SetDescription) {
    NIpse::CRlAgentDef def;
    def.SetDescription("Test description");
    EXPECT_EQ(def.GetDescription(), "Test description");
}

TEST(CRlAgentDefTest, SetDefaultLearningRate) {
    NIpse::CRlAgentDef def;
    def.SetDefaultLearningRate(0.05f);
    EXPECT_FLOAT_EQ(def.GetDefaultLearningRate(), 0.05f);
}

TEST(CRlAgentDefTest, SetDefaultDiscountFactor) {
    NIpse::CRlAgentDef def;
    def.SetDefaultDiscountFactor(0.95f);
    EXPECT_FLOAT_EQ(def.GetDefaultDiscountFactor(), 0.95f);
}

TEST(CRlAgentDefTest, SetDefaultExplorationRate) {
    NIpse::CRlAgentDef def;
    def.SetDefaultExplorationRate(0.2f);
    EXPECT_FLOAT_EQ(def.GetDefaultExplorationRate(), 0.2f);
}

TEST(CRlAgentDefTest, SetMaxEpisodes) {
    NIpse::CRlAgentDef def;
    def.SetMaxEpisodes(5000);
    EXPECT_EQ(def.GetMaxEpisodes(), 5000u);
}

TEST(CRlAgentDefTest, SetMaxStepsPerEpisode) {
    NIpse::CRlAgentDef def;
    def.SetMaxStepsPerEpisode(200);
    EXPECT_EQ(def.GetMaxStepsPerEpisode(), 200u);
}

TEST(CRlAgentDefTest, IsValid) {
    NIpse::CRlAgentDef def;
    EXPECT_FALSE(def.IsValid());

    def.SetName("TestDef");
    EXPECT_TRUE(def.IsValid());
}

TEST(CRlAgentDefTest, IsValidWithInvalidLearningRate) {
    NIpse::CRlAgentDef def;
    def.SetName("TestDef");
    def.SetDefaultLearningRate(-0.01f);
    EXPECT_FALSE(def.IsValid());
}

TEST(CRlAgentDefTest, IsValidWithInvalidDiscountFactor) {
    NIpse::CRlAgentDef def;
    def.SetName("TestDef");
    def.SetDefaultDiscountFactor(1.5f);
    EXPECT_FALSE(def.IsValid());
}

TEST(CRlAgentDefTest, Reset) {
    NIpse::CRlAgentDef def(42, "TestDef");
    def.SetDefaultLearningRate(0.05f);
    def.SetDefaultDiscountFactor(0.95f);
    def.SetDefaultExplorationRate(0.2f);
    def.SetMaxEpisodes(5000);
    def.SetMaxStepsPerEpisode(200);

    def.Reset();

    EXPECT_FLOAT_EQ(def.GetDefaultLearningRate(), 0.01f);
    EXPECT_FLOAT_EQ(def.GetDefaultDiscountFactor(), 0.99f);
    EXPECT_FLOAT_EQ(def.GetDefaultExplorationRate(), 0.1f);
    EXPECT_EQ(def.GetMaxEpisodes(), 1000u);
    EXPECT_EQ(def.GetMaxStepsPerEpisode(), 100u);
}
