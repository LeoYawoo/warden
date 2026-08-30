#include <gtest/gtest.h>
#include "NTempest/CMath.h"
#include <cmath>

using namespace NTempest;

TEST(CMathTest, Constants) {
    EXPECT_NEAR(CMath::PI, 3.1415927f, 0.0001f);
    EXPECT_NEAR(CMath::TWO_PI, 6.2831855f, 0.0001f);
    EXPECT_NEAR(CMath::DEG_TO_RAD, 3.1415927f / 180.0f, 0.0001f);
    EXPECT_NEAR(CMath::RAD_TO_DEG, 180.0f / 3.1415927f, 0.0001f);
}

TEST(CMathTest, Fint) {
    EXPECT_EQ(CMath::fint(1.5f), 1);
    EXPECT_EQ(CMath::fint(-1.5f), -1);
    EXPECT_EQ(CMath::fint(0.0f), 0);
}

TEST(CMathTest, FintN) {
    EXPECT_EQ(CMath::fint_n(1.4f), 1);
    EXPECT_EQ(CMath::fint_n(1.5f), 2);
    EXPECT_EQ(CMath::fint_n(-1.4f), -1);
    EXPECT_EQ(CMath::fint_n(-1.5f), -2);
}

TEST(CMathTest, Sqrt) {
    EXPECT_NEAR(CMath::sqrt(4.0f), 2.0f, 0.001f);
    EXPECT_NEAR(CMath::sqrt(9.0f), 3.0f, 0.001f);
    EXPECT_NEAR(CMath::sqrt(0.0f), 0.0f, 0.001f);
}

TEST(CMathTest, Sin) {
    EXPECT_NEAR(CMath::sin(0.0f), 0.0f, 0.001f);
    EXPECT_NEAR(CMath::sin(CMath::PI / 2.0f), 1.0f, 0.001f);
    EXPECT_NEAR(CMath::sin(CMath::PI), 0.0f, 0.001f);
}

TEST(CMathTest, Cos) {
    EXPECT_NEAR(CMath::cos(0.0f), 1.0f, 0.001f);
    EXPECT_NEAR(CMath::cos(CMath::PI / 2.0f), 0.0f, 0.001f);
    EXPECT_NEAR(CMath::cos(CMath::PI), -1.0f, 0.001f);
}

TEST(CMathTest, Tan) {
    EXPECT_NEAR(CMath::tan(0.0f), 0.0f, 0.001f);
    EXPECT_NEAR(CMath::tan(CMath::PI / 4.0f), 1.0f, 0.001f);
}

TEST(CMathTest, Asin) {
    EXPECT_NEAR(CMath::asin(0.0f), 0.0f, 0.001f);
    EXPECT_NEAR(CMath::asin(1.0f), CMath::PI / 2.0f, 0.001f);
}

TEST(CMathTest, Acos) {
    EXPECT_NEAR(CMath::acos(1.0f), 0.0f, 0.001f);
    EXPECT_NEAR(CMath::acos(0.0f), CMath::PI / 2.0f, 0.001f);
}

TEST(CMathTest, Atan2) {
    EXPECT_NEAR(CMath::atan2(0.0f, 1.0f), 0.0f, 0.001f);
    EXPECT_NEAR(CMath::atan2(1.0f, 0.0f), CMath::PI / 2.0f, 0.001f);
}

TEST(CMathTest, Abs) {
    EXPECT_FLOAT_EQ(CMath::Abs(5.0f), 5.0f);
    EXPECT_FLOAT_EQ(CMath::Abs(-5.0f), 5.0f);
    EXPECT_FLOAT_EQ(CMath::Abs(0.0f), 0.0f);
}

TEST(CMathTest, Min) {
    EXPECT_FLOAT_EQ(CMath::Min(3.0f, 5.0f), 3.0f);
    EXPECT_FLOAT_EQ(CMath::Min(5.0f, 3.0f), 3.0f);
}

TEST(CMathTest, Max) {
    EXPECT_FLOAT_EQ(CMath::Max(3.0f, 5.0f), 5.0f);
    EXPECT_FLOAT_EQ(CMath::Max(5.0f, 3.0f), 5.0f);
}

TEST(CMathTest, Clamp) {
    EXPECT_FLOAT_EQ(CMath::Clamp(5.0f, 0.0f, 10.0f), 5.0f);
    EXPECT_FLOAT_EQ(CMath::Clamp(-5.0f, 0.0f, 10.0f), 0.0f);
    EXPECT_FLOAT_EQ(CMath::Clamp(15.0f, 0.0f, 10.0f), 10.0f);
}

TEST(CMathTest, Lerp) {
    EXPECT_FLOAT_EQ(CMath::Lerp(0.0f, 10.0f, 0.0f), 0.0f);
    EXPECT_FLOAT_EQ(CMath::Lerp(0.0f, 10.0f, 1.0f), 10.0f);
    EXPECT_FLOAT_EQ(CMath::Lerp(0.0f, 10.0f, 0.5f), 5.0f);
}

TEST(CMathTest, DegToRad) {
    EXPECT_NEAR(CMath::DegToRad(180.0f), CMath::PI, 0.001f);
    EXPECT_NEAR(CMath::DegToRad(90.0f), CMath::PI / 2.0f, 0.001f);
}

TEST(CMathTest, RadToDeg) {
    EXPECT_NEAR(CMath::RadToDeg(CMath::PI), 180.0f, 0.001f);
    EXPECT_NEAR(CMath::RadToDeg(CMath::PI / 2.0f), 90.0f, 0.001f);
}
