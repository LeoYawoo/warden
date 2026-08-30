#include <gtest/gtest.h>
#include "Agile/Float.h"

TEST(FloatTest, DefaultConstructor) {
    Float f;
    EXPECT_FLOAT_EQ(f.GetValue(), 0.0f);
}

TEST(FloatTest, ValueConstructor) {
    Float f(3.14f);
    EXPECT_FLOAT_EQ(f.GetValue(), 3.14f);
}

TEST(FloatTest, SetValue) {
    Float f;
    f.SetValue(2.71f);
    EXPECT_FLOAT_EQ(f.GetValue(), 2.71f);
}

TEST(FloatTest, AddAssign) {
    Float a(1.0f);
    Float b(2.0f);
    a += b;
    EXPECT_FLOAT_EQ(a.GetValue(), 3.0f);
}

TEST(FloatTest, SubtractAssign) {
    Float a(5.0f);
    Float b(3.0f);
    a -= b;
    EXPECT_FLOAT_EQ(a.GetValue(), 2.0f);
}

TEST(FloatTest, MultiplyAssign) {
    Float f(4.0f);
    f *= 2.0f;
    EXPECT_FLOAT_EQ(f.GetValue(), 8.0f);
}

TEST(FloatTest, DivideAssign) {
    Float f(10.0f);
    f /= 2.0f;
    EXPECT_FLOAT_EQ(f.GetValue(), 5.0f);
}

TEST(FloatTest, DivideByZero) {
    Float f(10.0f);
    f /= 0.0f;
    EXPECT_FLOAT_EQ(f.GetValue(), 10.0f);  // Should remain unchanged
}

TEST(FloatTest, Add) {
    Float a(1.0f);
    Float b(2.0f);
    Float c = a + b;
    EXPECT_FLOAT_EQ(c.GetValue(), 3.0f);
}

TEST(FloatTest, Subtract) {
    Float a(5.0f);
    Float b(3.0f);
    Float c = a - b;
    EXPECT_FLOAT_EQ(c.GetValue(), 2.0f);
}

TEST(FloatTest, Equality) {
    Float a(1.0f);
    Float b(1.0f);
    Float c(2.0f);
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
}

TEST(FloatTest, Inequality) {
    Float a(1.0f);
    Float b(2.0f);
    EXPECT_TRUE(a != b);
}

TEST(FloatTest, LessThan) {
    Float a(1.0f);
    Float b(2.0f);
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST(FloatTest, GreaterThan) {
    Float a(2.0f);
    Float b(1.0f);
    EXPECT_TRUE(a > b);
    EXPECT_FALSE(b > a);
}

TEST(FloatTest, ImplicitConversion) {
    Float f(3.14f);
    float val = f;
    EXPECT_FLOAT_EQ(val, 3.14f);
}

TEST(FloatTest, ChainedOperations) {
    Float a(1.0f);
    Float b(2.0f);
    Float c(3.0f);
    a += b;
    a -= c;
    EXPECT_FLOAT_EQ(a.GetValue(), 0.0f);
}
