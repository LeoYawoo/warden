#include <gtest/gtest.h>
#include "Tempest/C2Vector.h"
#include <cmath>

using namespace Tempest;

TEST(C2VectorTest, DefaultConstructor) {
    C2Vector v;
    EXPECT_FLOAT_EQ(v.x, 0.0f);
    EXPECT_FLOAT_EQ(v.y, 0.0f);
}

TEST(C2VectorTest, ParameterizedConstructor) {
    C2Vector v(3.0f, 4.0f);
    EXPECT_FLOAT_EQ(v.x, 3.0f);
    EXPECT_FLOAT_EQ(v.y, 4.0f);
}

TEST(C2VectorTest, Equality) {
    C2Vector a(1.0f, 2.0f);
    C2Vector b(1.0f, 2.0f);
    C2Vector c(3.0f, 4.0f);
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
}

TEST(C2VectorTest, Inequality) {
    C2Vector a(1.0f, 2.0f);
    C2Vector b(3.0f, 4.0f);
    EXPECT_TRUE(a != b);
}

TEST(C2VectorTest, SquaredMagnitude) {
    C2Vector v(3.0f, 4.0f);
    EXPECT_FLOAT_EQ(v.SquaredMag(), 25.0f);
}

TEST(C2VectorTest, Magnitude) {
    C2Vector v(3.0f, 4.0f);
    EXPECT_FLOAT_EQ(v.Mag(), 5.0f);
}

TEST(C2VectorTest, Dot) {
    C2Vector a(1.0f, 2.0f);
    C2Vector b(3.0f, 4.0f);
    EXPECT_FLOAT_EQ(a.Dot(b), 11.0f);
}

TEST(C2VectorTest, Add) {
    C2Vector a(1.0f, 2.0f);
    C2Vector b(3.0f, 4.0f);
    C2Vector c = a + b;
    EXPECT_FLOAT_EQ(c.x, 4.0f);
    EXPECT_FLOAT_EQ(c.y, 6.0f);
}

TEST(C2VectorTest, Subtract) {
    C2Vector a(5.0f, 6.0f);
    C2Vector b(3.0f, 4.0f);
    C2Vector c = a - b;
    EXPECT_FLOAT_EQ(c.x, 2.0f);
    EXPECT_FLOAT_EQ(c.y, 2.0f);
}

TEST(C2VectorTest, ScalarMultiply) {
    C2Vector v(2.0f, 3.0f);
    C2Vector result = v * 2.0f;
    EXPECT_FLOAT_EQ(result.x, 4.0f);
    EXPECT_FLOAT_EQ(result.y, 6.0f);
}

TEST(C2VectorTest, ScalarMultiplyReverse) {
    C2Vector v(2.0f, 3.0f);
    C2Vector result = 2.0f * v;
    EXPECT_FLOAT_EQ(result.x, 4.0f);
    EXPECT_FLOAT_EQ(result.y, 6.0f);
}

TEST(C2VectorTest, ScalarDivide) {
    C2Vector v(4.0f, 6.0f);
    C2Vector result = v / 2.0f;
    EXPECT_FLOAT_EQ(result.x, 2.0f);
    EXPECT_FLOAT_EQ(result.y, 3.0f);
}

TEST(C2VectorTest, AddAssign) {
    C2Vector a(1.0f, 2.0f);
    C2Vector b(3.0f, 4.0f);
    a += b;
    EXPECT_FLOAT_EQ(a.x, 4.0f);
    EXPECT_FLOAT_EQ(a.y, 6.0f);
}

TEST(C2VectorTest, SubtractAssign) {
    C2Vector a(5.0f, 6.0f);
    C2Vector b(3.0f, 4.0f);
    a -= b;
    EXPECT_FLOAT_EQ(a.x, 2.0f);
    EXPECT_FLOAT_EQ(a.y, 2.0f);
}

TEST(C2VectorTest, ScalarMultiplyAssign) {
    C2Vector v(2.0f, 3.0f);
    v *= 2.0f;
    EXPECT_FLOAT_EQ(v.x, 4.0f);
    EXPECT_FLOAT_EQ(v.y, 6.0f);
}

TEST(C2VectorTest, FromAxisAngle) {
    C2Vector v;
    v.FromAxisAngle(0.0f);
    EXPECT_NEAR(v.x, 0.0f, 0.001f);
    EXPECT_NEAR(v.y, 1.0f, 0.001f);

    v.FromAxisAngle(3.1415927f / 2.0f);
    EXPECT_NEAR(v.x, 1.0f, 0.001f);
    EXPECT_NEAR(v.y, 0.0f, 0.001f);
}
