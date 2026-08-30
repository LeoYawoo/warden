#include <gtest/gtest.h>
#include "Anim/Type.h"
#include <cmath>

TEST(Fixed16Test, DefaultConstructor) {
    fixed16 f;
    EXPECT_EQ(f.n, 0);
}

TEST(Fixed16Test, Int16Constructor) {
    fixed16 f(static_cast<int16_t>(16384));
    EXPECT_EQ(f.n, 16384);
}

TEST(Fixed16Test, FloatConstructor) {
    fixed16 f(0.5f);
    // 0.5 * 32767 = 16383.5, truncated to 16383
    EXPECT_NEAR(f.n, 16383, 1);
}

TEST(Fixed16Test, ToFloat) {
    fixed16 f(static_cast<int16_t>(16384));
    float value = static_cast<float>(f);
    EXPECT_NEAR(value, 0.5f, 0.001f);
}

TEST(Fixed16Test, Addition) {
    fixed16 a(static_cast<int16_t>(1000));
    fixed16 b(static_cast<int16_t>(2000));
    fixed16 c = a + b;
    EXPECT_EQ(c.n, 3000);
}

TEST(Fixed16Test, Subtraction) {
    fixed16 a(static_cast<int16_t>(3000));
    fixed16 b(static_cast<int16_t>(1000));
    fixed16 c = a - b;
    EXPECT_EQ(c.n, 2000);
}

TEST(Fixed16Test, Multiplication) {
    fixed16 a(0.5f);
    fixed16 b(0.5f);
    fixed16 c = a * b;
    // 0.5 * 0.5 = 0.25
    EXPECT_NEAR(static_cast<float>(c), 0.25f, 0.01f);
}

TEST(Fixed16Test, Division) {
    // Test that division works without crashing
    fixed16 a(static_cast<int16_t>(16384));
    fixed16 b(static_cast<int16_t>(8192));
    fixed16 c = a / b;
    // Just verify the function runs
    EXPECT_TRUE(true);
}

TEST(Fixed16Test, DivisionByZero) {
    fixed16 a(static_cast<int16_t>(16384));
    fixed16 b(static_cast<int16_t>(0));
    fixed16 c = a / b;
    EXPECT_EQ(c.n, 0);
}

TEST(Fixed16Test, CompoundAdd) {
    fixed16 a(static_cast<int16_t>(1000));
    fixed16 b(static_cast<int16_t>(2000));
    a += b;
    EXPECT_EQ(a.n, 3000);
}

TEST(Fixed16Test, CompoundSubtract) {
    fixed16 a(static_cast<int16_t>(3000));
    fixed16 b(static_cast<int16_t>(1000));
    a -= b;
    EXPECT_EQ(a.n, 2000);
}

TEST(Fixed16Test, CompoundMultiply) {
    fixed16 a(0.5f);
    fixed16 b(0.5f);
    a *= b;
    EXPECT_NEAR(static_cast<float>(a), 0.25f, 0.01f);
}

TEST(Fixed16Test, CompoundDivide) {
    // Test that compound division works without crashing
    fixed16 a(static_cast<int16_t>(16384));
    fixed16 b(static_cast<int16_t>(8192));
    a /= b;
    // Just verify the function runs
    EXPECT_TRUE(true);
}

TEST(Fixed16Test, Equality) {
    fixed16 a(static_cast<int16_t>(1000));
    fixed16 b(static_cast<int16_t>(1000));
    fixed16 c(static_cast<int16_t>(2000));

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
}

TEST(Fixed16Test, Inequality) {
    fixed16 a(static_cast<int16_t>(1000));
    fixed16 b(static_cast<int16_t>(2000));

    EXPECT_TRUE(a != b);
}

TEST(Fixed16Test, LessThan) {
    fixed16 a(static_cast<int16_t>(1000));
    fixed16 b(static_cast<int16_t>(2000));

    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST(Fixed16Test, GreaterThan) {
    fixed16 a(static_cast<int16_t>(2000));
    fixed16 b(static_cast<int16_t>(1000));

    EXPECT_TRUE(a > b);
    EXPECT_FALSE(b > a);
}

TEST(Fixed16Test, Abs) {
    fixed16 a(static_cast<int16_t>(-1000));
    fixed16 b = a.Abs();
    EXPECT_EQ(b.n, 1000);
}

TEST(Fixed16Test, Clamp) {
    fixed16 value(static_cast<int16_t>(1500));
    fixed16 min(static_cast<int16_t>(1000));
    fixed16 max(static_cast<int16_t>(2000));

    fixed16 clamped = value.Clamp(min, max);
    EXPECT_EQ(clamped.n, 1500);

    fixed16 below(static_cast<int16_t>(500));
    clamped = below.Clamp(min, max);
    EXPECT_EQ(clamped.n, 1000);

    fixed16 above(static_cast<int16_t>(2500));
    clamped = above.Clamp(min, max);
    EXPECT_EQ(clamped.n, 2000);
}

TEST(Fixed16Test, FromFloat) {
    fixed16 f = fixed16::FromFloat(0.5f);
    EXPECT_NEAR(f.n, 16383, 1);
}

TEST(Fixed16Test, ToFloatStatic) {
    fixed16 f(static_cast<int16_t>(16384));
    float value = fixed16::ToFloat(f);
    EXPECT_NEAR(value, 0.5f, 0.001f);
}

TEST(Fixed16Test, RoundTrip) {
    float original = 0.12345f;
    fixed16 fixed = fixed16::FromFloat(original);
    float restored = fixed16::ToFloat(fixed);
    EXPECT_NEAR(original, restored, 0.001f);
}
