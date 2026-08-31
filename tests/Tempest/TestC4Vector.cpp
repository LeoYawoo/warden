#include <gtest/gtest.h>
#include "Tempest/C4Vector.h"
#include <cmath>

using namespace Tempest;

TEST(C4VectorTest, DefaultConstructor) {
    C4Vector v;
    EXPECT_FLOAT_EQ(v.x, 0.0f);
    EXPECT_FLOAT_EQ(v.y, 0.0f);
    EXPECT_FLOAT_EQ(v.z, 0.0f);
    EXPECT_FLOAT_EQ(v.w, 0.0f);
}

TEST(C4VectorTest, ParameterizedConstructor) {
    C4Vector v(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_FLOAT_EQ(v.x, 1.0f);
    EXPECT_FLOAT_EQ(v.y, 2.0f);
    EXPECT_FLOAT_EQ(v.z, 3.0f);
    EXPECT_FLOAT_EQ(v.w, 4.0f);
}

TEST(C4VectorTest, SquaredMagnitude) {
    C4Vector v(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_FLOAT_EQ(v.SquaredMag(), 30.0f);
}

TEST(C4VectorTest, Magnitude) {
    C4Vector v(1.0f, 0.0f, 0.0f, 0.0f);
    EXPECT_FLOAT_EQ(v.Mag(), 1.0f);
}

TEST(C4VectorTest, Dot) {
    C4Vector a(1.0f, 2.0f, 3.0f, 4.0f);
    C4Vector b(5.0f, 6.0f, 7.0f, 8.0f);
    EXPECT_FLOAT_EQ(a.Dot(b), 70.0f);
}

TEST(C4VectorTest, Add) {
    C4Vector a(1.0f, 2.0f, 3.0f, 4.0f);
    C4Vector b(5.0f, 6.0f, 7.0f, 8.0f);
    C4Vector c = a + b;
    EXPECT_FLOAT_EQ(c.x, 6.0f);
    EXPECT_FLOAT_EQ(c.y, 8.0f);
    EXPECT_FLOAT_EQ(c.z, 10.0f);
    EXPECT_FLOAT_EQ(c.w, 12.0f);
}

TEST(C4VectorTest, Subtract) {
    C4Vector a(5.0f, 6.0f, 7.0f, 8.0f);
    C4Vector b(1.0f, 2.0f, 3.0f, 4.0f);
    C4Vector c = a - b;
    EXPECT_FLOAT_EQ(c.x, 4.0f);
    EXPECT_FLOAT_EQ(c.y, 4.0f);
    EXPECT_FLOAT_EQ(c.z, 4.0f);
    EXPECT_FLOAT_EQ(c.w, 4.0f);
}

TEST(C4VectorTest, ScalarMultiply) {
    C4Vector v(1.0f, 2.0f, 3.0f, 4.0f);
    C4Vector result = v * 2.0f;
    EXPECT_FLOAT_EQ(result.x, 2.0f);
    EXPECT_FLOAT_EQ(result.y, 4.0f);
    EXPECT_FLOAT_EQ(result.z, 6.0f);
    EXPECT_FLOAT_EQ(result.w, 8.0f);
}

TEST(C4VectorTest, ScalarMultiplyReverse) {
    C4Vector v(1.0f, 2.0f, 3.0f, 4.0f);
    C4Vector result = 2.0f * v;
    EXPECT_FLOAT_EQ(result.x, 2.0f);
    EXPECT_FLOAT_EQ(result.y, 4.0f);
    EXPECT_FLOAT_EQ(result.z, 6.0f);
    EXPECT_FLOAT_EQ(result.w, 8.0f);
}

TEST(C4VectorTest, DivideAssign) {
    C4Vector v(2.0f, 4.0f, 6.0f, 8.0f);
    v /= 2.0f;
    EXPECT_FLOAT_EQ(v.x, 1.0f);
    EXPECT_FLOAT_EQ(v.y, 2.0f);
    EXPECT_FLOAT_EQ(v.z, 3.0f);
    EXPECT_FLOAT_EQ(v.w, 4.0f);
}

TEST(C4VectorTest, Normalize) {
    C4Vector v(1.0f, 0.0f, 0.0f, 0.0f);
    v.Normalize();
    EXPECT_NEAR(v.Mag(), 1.0f, 0.001f);
}
