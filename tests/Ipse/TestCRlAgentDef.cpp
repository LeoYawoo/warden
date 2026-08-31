#include <gtest/gtest.h>
#include "Ipse/CRlAgentDef.h"

TEST(CRlAgentDefTest, DefaultConstructor) {
    Ipse::CRlAgentDef def;
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
    Ipse::CRlAgentDef def(42, "TestDef");
    EXPECT_EQ(def.GetId(), 42u);
    EXPECT_EQ(def.GetName(), "TestDef");
}

TEST(CRlAgentDefTest, SetId) {
    Ipse::CRlAgentDef def;
    def.SetId(100);
    EXPECT_EQ(def.GetId(), 100u);
}

TEST(CRlAgentDefTest, SetName) {
    Ipse::CRlAgentDef def;
    def.SetName("NewName");
    EXPECT_EQ(def.GetName(), "NewName");
}

TEST(CRlAgentDefTest, SetDescription) {
    Ipse::CRlAgentDef def;
    def.SetDescription("Test description");
    EXPECT_EQ(def.GetDescription(), "Test description");
}

TEST(CRlAgentDefTest, SetDefaultLearningRate) {
    Ipse::CRlAgentDef def;
    def.SetDefaultLearningRate(0.05f);
    EXPECT_FLOAT_EQ(def.GetDefaultLearningRate(), 0.05f);
}

TEST(CRlAgentDefTest, SetDefaultDiscountFactor) {
    Ipse::CRlAgentDef def;
    def.SetDefaultDiscountFactor(0.95f);
    EXPECT_FLOAT_EQ(def.GetDefaultDiscountFactor(), 0.95f);
}

TEST(CRlAgentDefTest, SetDefaultExplorationRate) {
    Ipse::CRlAgentDef def;
    def.SetDefaultExplorationRate(0.2f);
    EXPECT_FLOAT_EQ(def.GetDefaultExplorationRate(), 0.2f);
}

TEST(CRlAgentDefTest, SetMaxEpisodes) {
    Ipse::CRlAgentDef def;
    def.SetMaxEpisodes(5000);
    EXPECT_EQ(def.GetMaxEpisodes(), 5000u);
}

TEST(CRlAgentDefTest, SetMaxStepsPerEpisode) {
    Ipse::CRlAgentDef def;
    def.SetMaxStepsPerEpisode(200);
    EXPECT_EQ(def.GetMaxStepsPerEpisode(), 200u);
}

TEST(CRlAgentDefTest, IsValid) {
    Ipse::CRlAgentDef def;
    EXPECT_FALSE(def.IsValid());

    def.SetName("TestDef");
    EXPECT_TRUE(def.IsValid());
}

TEST(CRlAgentDefTest, IsValidWithInvalidLearningRate) {
    Ipse::CRlAgentDef def;
    def.SetName("TestDef");
    def.SetDefaultLearningRate(-0.01f);
    EXPECT_FALSE(def.IsValid());
}

TEST(CRlAgentDefTest, IsValidWithInvalidDiscountFactor) {
    Ipse::CRlAgentDef def;
    def.SetName("TestDef");
    def.SetDefaultDiscountFactor(1.5f);
    EXPECT_FALSE(def.IsValid());
}

TEST(CRlAgentDefTest, Reset) {
    Ipse::CRlAgentDef def(42, "TestDef");
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
