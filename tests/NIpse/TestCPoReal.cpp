#include <gtest/gtest.h>
#include "NIpse/CPoReal.h"
#include <cmath>

TEST(CPoRealTest, DefaultConstructor) {
    NIpse::CPoReal po;
    EXPECT_FLOAT_EQ(po.GetValue(), 0.0f);
    EXPECT_FLOAT_EQ(po.GetTarget(), 0.0f);
    EXPECT_FLOAT_EQ(po.GetVelocity(), 0.0f);
    EXPECT_FLOAT_EQ(po.GetMin(), 0.0f);
    EXPECT_FLOAT_EQ(po.GetMax(), 1.0f);
    EXPECT_FALSE(po.IsActive());
}

TEST(CPoRealTest, ParameterizedConstructor) {
    NIpse::CPoReal po(0.5f, 1.0f);
    EXPECT_FLOAT_EQ(po.GetValue(), 0.5f);
    EXPECT_FLOAT_EQ(po.GetTarget(), 1.0f);
    EXPECT_FLOAT_EQ(po.GetVelocity(), 0.0f);
    EXPECT_FLOAT_EQ(po.GetMin(), 0.0f);
    EXPECT_FLOAT_EQ(po.GetMax(), 1.0f);
    EXPECT_FALSE(po.IsActive());
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

TEST(CPoRealTest, SetVelocity) {
    NIpse::CPoReal po;
    po.SetVelocity(1.5f);
    EXPECT_FLOAT_EQ(po.GetVelocity(), 1.5f);
}

TEST(CPoRealTest, SetRange) {
    NIpse::CPoReal po;
    po.SetRange(-1.0f, 2.0f);
    EXPECT_FLOAT_EQ(po.GetMin(), -1.0f);
    EXPECT_FLOAT_EQ(po.GetMax(), 2.0f);
}

TEST(CPoRealTest, SetActive) {
    NIpse::CPoReal po;
    po.SetActive(true);
    EXPECT_TRUE(po.IsActive());
    po.SetActive(false);
    EXPECT_FALSE(po.IsActive());
}

TEST(CPoRealTest, UpdateInactive) {
    NIpse::CPoReal po(0.5f, 1.0f);
    po.SetVelocity(1.0f);
    po.SetActive(false);

    po.Update(1.0f);
    EXPECT_FLOAT_EQ(po.GetValue(), 0.5f);
}

TEST(CPoRealTest, UpdateActive) {
    NIpse::CPoReal po(0.0f, 1.0f);
    po.SetVelocity(1.0f);
    po.SetActive(true);

    po.Update(0.5f);
    EXPECT_FLOAT_EQ(po.GetValue(), 0.5f);
}

TEST(CPoRealTest, UpdateClamp) {
    NIpse::CPoReal po(0.0f, 2.0f);
    po.SetVelocity(1.0f);
    po.SetRange(0.0f, 1.0f);
    po.SetActive(true);

    po.Update(2.0f);
    EXPECT_FLOAT_EQ(po.GetValue(), 1.0f);
}

TEST(CPoRealTest, HasReachedTarget) {
    NIpse::CPoReal po(0.5f, 0.5f);
    EXPECT_TRUE(po.HasReachedTarget());

    NIpse::CPoReal po2(0.5f, 0.6f);
    EXPECT_FALSE(po2.HasReachedTarget());
}

TEST(CPoRealTest, Reset) {
    NIpse::CPoReal po(0.5f, 1.0f);
    po.SetVelocity(2.0f);
    po.SetActive(true);

    po.Reset(0.25f);
    EXPECT_FLOAT_EQ(po.GetValue(), 0.25f);
    EXPECT_FLOAT_EQ(po.GetTarget(), 0.25f);
    EXPECT_FLOAT_EQ(po.GetVelocity(), 0.0f);
    EXPECT_FALSE(po.IsActive());
}

TEST(CPoRealTest, UpdateTowardsTarget) {
    NIpse::CPoReal po(0.0f, 1.0f);
    po.SetVelocity(0.5f);
    po.SetActive(true);

    po.Update(1.0f);
    EXPECT_FLOAT_EQ(po.GetValue(), 0.5f);

    po.Update(1.0f);
    EXPECT_FLOAT_EQ(po.GetValue(), 1.0f);
}
