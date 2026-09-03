#include <gtest/gtest.h>
#include "Ipse/CPoReal.h"
#include <cmath>

TEST(CPoRealTest, DefaultConstructor) {
    NIpse::CPoReal po;
    EXPECT_FLOAT_EQ(po.GetValue(), 0.0f);
    EXPECT_FLOAT_EQ(po.GetTarget(), 0.0f);
}

TEST(CPoRealTest, ParameterizedConstructor) {
    NIpse::CPoReal po(0.5f, 1.0f);
    EXPECT_FLOAT_EQ(po.GetValue(), 0.5f);
    EXPECT_FLOAT_EQ(po.GetTarget(), 1.0f);
}

TEST(CPoRealTest, SetValue) {
    NIpse::CPoReal po;
    po.SetValue(0.75f);
    EXPECT_FLOAT_EQ(po.GetValue(), 0.75f);
}

TEST(CPoRealTest, SetTarget) {
    NIpse::CPoReal po;
    po.SetTarget(0.9f);
    EXPECT_FLOAT_EQ(po.GetTarget(), 0.9f);
}

TEST(CPoRealTest, HasReachedTarget) {
    NIpse::CPoReal po(0.5f, 0.5f);
    EXPECT_TRUE(po.HasReachedTarget());

    NIpse::CPoReal po2(0.5f, 0.6f);
    EXPECT_FALSE(po2.HasReachedTarget());
}

TEST(CPoRealTest, Update) {
    NIpse::CPoReal po(0.0f, 1.0f);
    po.Update(0.5f);
    EXPECT_FALSE(po.HasReachedTarget());
    po.Update(0.6f);
    EXPECT_TRUE(po.HasReachedTarget());
}
