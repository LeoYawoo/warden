#include <gtest/gtest.h>
#include "Ipse/CRlAgentDef.h"

TEST(CRlAgentDefTest, DefaultConstructor) {
    NIpse::CRlAgentDef def;
    EXPECT_EQ(def.GetDefId(), 0);
    EXPECT_TRUE(def.IsValid());
}

TEST(CRlAgentDefTest, SetDefId) {
    NIpse::CRlAgentDef def;
    def.SetDefId(100);
    EXPECT_EQ(def.GetDefId(), 100);
}

TEST(CRlAgentDefTest, SetDefName) {
    NIpse::CRlAgentDef def;
    def.SetDefName("TestDef");
    EXPECT_STREQ(def.GetDefName(), "TestDef");
}

TEST(CRlAgentDefTest, IsValid) {
    NIpse::CRlAgentDef def;
    EXPECT_TRUE(def.IsValid());

    def.SetValid(false);
    EXPECT_FALSE(def.IsValid());
}

TEST(CRlAgentDefTest, Reset) {
    NIpse::CRlAgentDef def;
    def.SetDefId(42);
    def.Reset();
    EXPECT_EQ(def.GetDefId(), 0);
    EXPECT_TRUE(def.IsValid());
}

TEST(CRlAgentDefTest, Clear) {
    NIpse::CRlAgentDef def;
    def.SetDefId(42);
    def.Clear();
    EXPECT_EQ(def.GetDefId(), 0);
    EXPECT_FALSE(def.IsValid());
}
