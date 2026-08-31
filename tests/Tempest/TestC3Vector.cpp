#include <gtest/gtest.h>
#include "Tempest/C3Vector.h"
#include <cmath>

using namespace Tempest;

TEST(C3VectorTest, DefaultConstructor) {
    C3Vector v;
    EXPECT_FLOAT_EQ(v.x, 0.0f);
    EXPECT_FLOAT_EQ(v.y, 0.0f);
    EXPECT_FLOAT_EQ(v.z, 0.0f);
}

TEST(C3VectorTest, ParameterizedConstructor) {
    C3Vector v(1.0f, 2.0f, 3.0f);
    EXPECT_FLOAT_EQ(v.x, 1.0f);
    EXPECT_FLOAT_EQ(v.y, 2.0f);
    EXPECT_FLOAT_EQ(v.z, 3.0f);
}

TEST(C3VectorTest, Equality) {
    C3Vector a(1.0f, 2.0f, 3.0f);
    C3Vector b(1.0f, 2.0f, 3.0f);
    C3Vector c(4.0f, 5.0f, 6.0f);
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
}

TEST(C3VectorTest, Inequality) {
    C3Vector a(1.0f, 2.0f, 3.0f);
    C3Vector b(4.0f, 5.0f, 6.0f);
    EXPECT_TRUE(a != b);
}

TEST(C3VectorTest, SquaredMagnitude) {
    C3Vector v(1.0f, 2.0f, 3.0f);
    EXPECT_FLOAT_EQ(v.SquaredMag(), 14.0f);
}

TEST(C3VectorTest, Magnitude) {
    C3Vector v(3.0f, 4.0f, 0.0f);
    EXPECT_FLOAT_EQ(v.Mag(), 5.0f);
}

TEST(C3VectorTest, Dot) {
    C3Vector a(1.0f, 2.0f, 3.0f);
    C3Vector b(4.0f, 5.0f, 6.0f);
    EXPECT_FLOAT_EQ(a.Dot(b), 32.0f);
}

TEST(C3VectorTest, Cross) {
    C3Vector a(1.0f, 0.0f, 0.0f);
    C3Vector b(0.0f, 1.0f, 0.0f);
    C3Vector c = a.Cross(b);
    EXPECT_FLOAT_EQ(c.x, 0.0f);
    EXPECT_FLOAT_EQ(c.y, 0.0f);
    EXPECT_FLOAT_EQ(c.z, 1.0f);
}

TEST(C3VectorTest, CrossAntiCommutative) {
    C3Vector a(1.0f, 2.0f, 3.0f);
    C3Vector b(4.0f, 5.0f, 6.0f);
    C3Vector ab = a.Cross(b);
    C3Vector ba = b.Cross(a);
    EXPECT_NEAR(ab.x, -ba.x, 0.001f);
    EXPECT_NEAR(ab.y, -ba.y, 0.001f);
    EXPECT_NEAR(ab.z, -ba.z, 0.001f);
}

TEST(C3VectorTest, Add) {
    C3Vector a(1.0f, 2.0f, 3.0f);
    C3Vector b(4.0f, 5.0f, 6.0f);
    C3Vector c = a + b;
    EXPECT_FLOAT_EQ(c.x, 5.0f);
    EXPECT_FLOAT_EQ(c.y, 7.0f);
    EXPECT_FLOAT_EQ(c.z, 9.0f);
}

TEST(C3VectorTest, Subtract) {
    C3Vector a(5.0f, 6.0f, 7.0f);
    C3Vector b(1.0f, 2.0f, 3.0f);
    C3Vector c = a - b;
    EXPECT_FLOAT_EQ(c.x, 4.0f);
    EXPECT_FLOAT_EQ(c.y, 4.0f);
    EXPECT_FLOAT_EQ(c.z, 4.0f);
}

TEST(C3VectorTest, ScalarMultiply) {
    C3Vector v(1.0f, 2.0f, 3.0f);
    C3Vector result = v * 2.0f;
    EXPECT_FLOAT_EQ(result.x, 2.0f);
    EXPECT_FLOAT_EQ(result.y, 4.0f);
    EXPECT_FLOAT_EQ(result.z, 6.0f);
}

TEST(C3VectorTest, ScalarMultiplyReverse) {
    C3Vector v(1.0f, 2.0f, 3.0f);
    C3Vector result = 2.0f * v;
    EXPECT_FLOAT_EQ(result.x, 2.0f);
    EXPECT_FLOAT_EQ(result.y, 4.0f);
    EXPECT_FLOAT_EQ(result.z, 6.0f);
}

TEST(C3VectorTest, ScalarDivide) {
    C3Vector v(2.0f, 4.0f, 6.0f);
    C3Vector result = v / 2.0f;
    EXPECT_FLOAT_EQ(result.x, 1.0f);
    EXPECT_FLOAT_EQ(result.y, 2.0f);
    EXPECT_FLOAT_EQ(result.z, 3.0f);
}

TEST(C3VectorTest, AddAssign) {
    C3Vector a(1.0f, 2.0f, 3.0f);
    C3Vector b(4.0f, 5.0f, 6.0f);
    a += b;
    EXPECT_FLOAT_EQ(a.x, 5.0f);
    EXPECT_FLOAT_EQ(a.y, 7.0f);
    EXPECT_FLOAT_EQ(a.z, 9.0f);
}

TEST(C3VectorTest, SubtractAssign) {
    C3Vector a(5.0f, 6.0f, 7.0f);
    C3Vector b(1.0f, 2.0f, 3.0f);
    a -= b;
    EXPECT_FLOAT_EQ(a.x, 4.0f);
    EXPECT_FLOAT_EQ(a.y, 4.0f);
    EXPECT_FLOAT_EQ(a.z, 4.0f);
}

TEST(C3VectorTest, ScalarMultiplyAssign) {
    C3Vector v(1.0f, 2.0f, 3.0f);
    v *= 2.0f;
    EXPECT_FLOAT_EQ(v.x, 2.0f);
    EXPECT_FLOAT_EQ(v.y, 4.0f);
    EXPECT_FLOAT_EQ(v.z, 6.0f);
}

TEST(C3VectorTest, Normalize) {
    C3Vector v(3.0f, 4.0f, 0.0f);
    v.Normalize();
    EXPECT_NEAR(v.Mag(), 1.0f, 0.001f);
    EXPECT_NEAR(v.x, 0.6f, 0.001f);
    EXPECT_NEAR(v.y, 0.8f, 0.001f);
    EXPECT_NEAR(v.z, 0.0f, 0.001f);
}

TEST(C3VectorTest, IsUnit) {
    C3Vector v(1.0f, 0.0f, 0.0f);
    EXPECT_TRUE(v.IsUnit());

    C3Vector v2(1.0f, 1.0f, 1.0f);
    EXPECT_FALSE(v2.IsUnit());
}

TEST(C3VectorTest, ProjectionOnPlane) {
    C3Vector point(1.0f, 1.0f, 1.0f);
    C3Vector planeNormal(0.0f, 0.0f, 1.0f);
    C3Vector result;
    result.ProjectionOnPlane(point, planeNormal);
    EXPECT_NEAR(result.x, 1.0f, 0.001f);
    EXPECT_NEAR(result.y, 1.0f, 0.001f);
    EXPECT_NEAR(result.z, 0.0f, 0.001f);
}
