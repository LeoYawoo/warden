#include <gtest/gtest.h>
#include "Ipse/CPoReal.h"
#include "Ipse/CPrRelation.h"
#include "Ipse/CRlAgent.h"
#include "Ipse/CRlAgentDef.h"
#include "Ipse/CRlProperty.h"
#include "Ipse/CThreadData.h"
#include <cmath>

// Test CPrRelation (new tests only)
TEST(CPrRelationTest, DefaultConstructor) {
    NIpse::CPrRelation relation;
    EXPECT_EQ(relation.GetRelationId(), 0);
    EXPECT_TRUE(relation.IsEnabled());
}

TEST(CPrRelationTest, SetRelationId) {
    NIpse::CPrRelation relation;
    relation.SetRelationId(42);
    EXPECT_EQ(relation.GetRelationId(), 42);
}

TEST(CPrRelationTest, SetEnabled) {
    NIpse::CPrRelation relation;
    relation.SetEnabled(false);
    EXPECT_FALSE(relation.IsEnabled());
}

TEST(CPrRelationTest, Reset) {
    NIpse::CPrRelation relation;
    relation.SetRelationId(42);
    relation.Reset();
    // Reset clears internal state, not relationId
    EXPECT_TRUE(relation.IsEnabled());
}

// Test CRlProperty (new tests only)
TEST(CRlPropertyTest, DefaultConstructor) {
    NIpse::CRlProperty prop;
    EXPECT_EQ(prop.GetPropertyId(), 0);
    EXPECT_FLOAT_EQ(prop.GetValue(), 0.0f);
    EXPECT_TRUE(prop.IsValid());
}

TEST(CRlPropertyTest, SetValue) {
    NIpse::CRlProperty prop;
    prop.SetValue(5.0f);
    EXPECT_FLOAT_EQ(prop.GetValue(), 5.0f);
}

TEST(CRlPropertyTest, SetValid) {
    NIpse::CRlProperty prop;
    prop.SetValid(false);
    EXPECT_FALSE(prop.IsValid());
}

// Test CThreadData (new tests only)
TEST(CThreadDataTest, DefaultConstructor) {
    NIpse::CThreadData data;
    EXPECT_EQ(data.GetThreadId(), 0);
    EXPECT_TRUE(data.IsValid());
}

TEST(CThreadDataTest, SetThreadId) {
    NIpse::CThreadData data;
    data.SetThreadId(42);
    EXPECT_EQ(data.GetThreadId(), 42);
}

TEST(CThreadDataTest, Initialize) {
    NIpse::CThreadData data;
    data.Initialize();
    EXPECT_TRUE(data.IsValid());
}

TEST(CThreadDataTest, Shutdown) {
    NIpse::CThreadData data;
    data.Initialize();
    data.Shutdown();
    EXPECT_FALSE(data.IsValid());
}
