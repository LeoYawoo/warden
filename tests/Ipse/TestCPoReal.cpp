#include <gtest/gtest.h>
#include "Ipse/CPoReal.h"
#include <cmath>

TEST(CPoRealTest, DefaultConstructor) {
    Ipse::CPoReal po;
    EXPECT_FLOAT_EQ(po.GetValue(), 0.0f);
    EXPECT_FLOAT_EQ(po.GetTarget(), 0.0f);
    EXPECT_FLOAT_EQ(po.GetVelocity(), 0.0f);
    EXPECT_FLOAT_EQ(po.GetMin(), 0.0f);
    EXPECT_FLOAT_EQ(po.GetMax(), 1.0f);
    EXPECT_FALSE(po.IsActive());
}

TEST(CPoRealTest, ParameterizedConstructor) {
    Ipse::CPoReal po(0.5f, 1.0f);
    EXPECT_FLOAT_EQ(po.GetValue(), 0.5f);
    EXPECT_FLOAT_EQ(po.GetTarget(), 1.0f);
    EXPECT_FLOAT_EQ(po.GetVelocity(), 0.0f);
    EXPECT_FLOAT_EQ(po.GetMin(), 0.0f);
    EXPECT_FLOAT_EQ(po.GetMax(), 1.0f);
    EXPECT_FALSE(po.IsActive());
}

TEST(CPoRealTest, SetValue) {
    Ipse::CPoReal po;
    po.SetValue(0.75f);
    EXPECT_FLOAT_EQ(po.GetValue(), 0.75f);
}

TEST(CPoRealTest, SetTarget) {
    Ipse::CPoReal po;
    po.SetTarget(0.9f);
    EXPECT_FLOAT_EQ(po.GetTarget(), 0.9f);
}

TEST(CPoRealTest, SetVelocity) {
    Ipse::CPoReal po;
    po.SetVelocity(1.5f);
    EXPECT_FLOAT_EQ(po.GetVelocity(), 1.5f);
}

TEST(CPoRealTest, SetRange) {
    Ipse::CPoReal po;
    po.SetRange(-1.0f, 2.0f);
    EXPECT_FLOAT_EQ(po.GetMin(), -1.0f);
    EXPECT_FLOAT_EQ(po.GetMax(), 2.0f);
}

TEST(CPoRealTest, SetActive) {
    Ipse::CPoReal po;
    po.SetActive(true);
    EXPECT_TRUE(po.IsActive());
    po.SetActive(false);
    EXPECT_FALSE(po.IsActive());
}

TEST(CPoRealTest, UpdateInactive) {
    Ipse::CPoReal po(0.5f, 1.0f);
    po.SetVelocity(1.0f);
    po.SetActive(false);

    po.Update(1.0f);
    EXPECT_FLOAT_EQ(po.GetValue(), 0.5f);
}

TEST(CPoRealTest, UpdateActive) {
    Ipse::CPoReal po(0.0f, 1.0f);
    po.SetVelocity(1.0f);
    po.SetActive(true);

    po.Update(0.5f);
    EXPECT_FLOAT_EQ(po.GetValue(), 0.5f);
}

TEST(CPoRealTest, UpdateClamp) {
    Ipse::CPoReal po(0.0f, 2.0f);
    po.SetVelocity(1.0f);
    po.SetRange(0.0f, 1.0f);
    po.SetActive(true);

    po.Update(2.0f);
    EXPECT_FLOAT_EQ(po.GetValue(), 1.0f);
}

TEST(CPoRealTest, HasReachedTarget) {
    Ipse::CPoReal po(0.5f, 0.5f);
    EXPECT_TRUE(po.HasReachedTarget());

    Ipse::CPoReal po2(0.5f, 0.6f);
    EXPECT_FALSE(po2.HasReachedTarget());
}

TEST(CPoRealTest, Reset) {
    Ipse::CPoReal po(0.5f, 1.0f);
    po.SetVelocity(2.0f);
    po.SetActive(true);

    po.Reset(0.25f);
    EXPECT_FLOAT_EQ(po.GetValue(), 0.25f);
    EXPECT_FLOAT_EQ(po.GetTarget(), 0.25f);
    EXPECT_FLOAT_EQ(po.GetVelocity(), 0.0f);
    EXPECT_FALSE(po.IsActive());
}

TEST(CPoRealTest, UpdateTowardsTarget) {
    Ipse::CPoReal po(0.0f, 1.0f);
    po.SetVelocity(0.5f);
    po.SetActive(true);

    po.Update(1.0f);
    EXPECT_FLOAT_EQ(po.GetValue(), 0.5f);

    po.Update(1.0f);
    EXPECT_FLOAT_EQ(po.GetValue(), 1.0f);
}
