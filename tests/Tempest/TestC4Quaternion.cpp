#include <gtest/gtest.h>
#include "Tempest/C4Quaternion.h"
#include <cmath>

using namespace Tempest;

TEST(C4QuaternionTest, DefaultConstructor) {
    C4Quaternion q;
    EXPECT_FLOAT_EQ(q.x, 0.0f);
    EXPECT_FLOAT_EQ(q.y, 0.0f);
    EXPECT_FLOAT_EQ(q.z, 0.0f);
    EXPECT_FLOAT_EQ(q.w, 1.0f);
}

TEST(C4QuaternionTest, ParameterizedConstructor) {
    C4Quaternion q(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_FLOAT_EQ(q.x, 1.0f);
    EXPECT_FLOAT_EQ(q.y, 2.0f);
    EXPECT_FLOAT_EQ(q.z, 3.0f);
    EXPECT_FLOAT_EQ(q.w, 4.0f);
}

TEST(C4QuaternionTest, SquaredMagnitude) {
    C4Quaternion q(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_FLOAT_EQ(q.SquaredMagnitude(), 30.0f);
}

TEST(C4QuaternionTest, Magnitude) {
    C4Quaternion q(1.0f, 0.0f, 0.0f, 0.0f);
    EXPECT_FLOAT_EQ(q.Magnitude(), 1.0f);
}

TEST(C4QuaternionTest, Dot) {
    C4Quaternion a(1.0f, 2.0f, 3.0f, 4.0f);
    C4Quaternion b(5.0f, 6.0f, 7.0f, 8.0f);
    EXPECT_FLOAT_EQ(a.Dot(b), 70.0f);
}

TEST(C4QuaternionTest, Conjugate) {
    C4Quaternion q(1.0f, 2.0f, 3.0f, 4.0f);
    C4Quaternion conj = q.Conjugate();
    EXPECT_FLOAT_EQ(conj.x, -1.0f);
    EXPECT_FLOAT_EQ(conj.y, -2.0f);
    EXPECT_FLOAT_EQ(conj.z, -3.0f);
    EXPECT_FLOAT_EQ(conj.w, 4.0f);
}

TEST(C4QuaternionTest, Inverse) {
    C4Quaternion q(0.0f, 0.0f, 0.7071f, 0.7071f);
    C4Quaternion inv = q.Inverse();
    C4Quaternion product = q * inv;
    EXPECT_NEAR(product.x, 0.0f, 0.01f);
    EXPECT_NEAR(product.y, 0.0f, 0.01f);
    EXPECT_NEAR(product.z, 0.0f, 0.01f);
    EXPECT_NEAR(product.w, 1.0f, 0.01f);
}

TEST(C4QuaternionTest, Normalize) {
    C4Quaternion q(1.0f, 2.0f, 3.0f, 4.0f);
    C4Quaternion n = q.Normalize();
    EXPECT_NEAR(n.Magnitude(), 1.0f, 0.001f);
}

TEST(C4QuaternionTest, Nlerp) {
    C4Quaternion q1(0.0f, 0.0f, 0.0f, 1.0f);
    C4Quaternion q2(0.0f, 0.0f, 0.7071f, 0.7071f);
    C4Quaternion result = C4Quaternion::Nlerp(0.5f, q1, q2);
    float mag = result.x*result.x + result.y*result.y + result.z*result.z + result.w*result.w;
    EXPECT_NEAR(mag, 1.0f, 0.01f);
}

TEST(C4QuaternionTest, Slerp) {
    C4Quaternion q1(0.0f, 0.0f, 0.0f, 1.0f);
    C4Quaternion q2(0.0f, 0.0f, 0.7071f, 0.7071f);
    C4Quaternion result = C4Quaternion::Slerp(0.5f, q1, q2);
    float mag = result.x*result.x + result.y*result.y + result.z*result.z + result.w*result.w;
    EXPECT_NEAR(mag, 1.0f, 0.01f);
}

TEST(C4QuaternionTest, Multiply) {
    C4Quaternion q1(0.0f, 0.0f, 0.0f, 1.0f);  // Identity
    C4Quaternion q2(1.0f, 0.0f, 0.0f, 0.0f);  // 180 degree around X
    C4Quaternion result = q1 * q2;
    EXPECT_NEAR(result.x, 1.0f, 0.001f);
    EXPECT_NEAR(result.y, 0.0f, 0.001f);
    EXPECT_NEAR(result.z, 0.0f, 0.001f);
    EXPECT_NEAR(result.w, 0.0f, 0.001f);
}

TEST(C4QuaternionTest, ScalarMultiply) {
    C4Quaternion q(1.0f, 2.0f, 3.0f, 4.0f);
    C4Quaternion result = q * 2.0f;
    EXPECT_FLOAT_EQ(result.x, 2.0f);
    EXPECT_FLOAT_EQ(result.y, 4.0f);
    EXPECT_FLOAT_EQ(result.z, 6.0f);
    EXPECT_FLOAT_EQ(result.w, 8.0f);
}

TEST(C4QuaternionTest, Add) {
    C4Quaternion a(1.0f, 2.0f, 3.0f, 4.0f);
    C4Quaternion b(5.0f, 6.0f, 7.0f, 8.0f);
    C4Quaternion result = a + b;
    EXPECT_FLOAT_EQ(result.x, 6.0f);
    EXPECT_FLOAT_EQ(result.y, 8.0f);
    EXPECT_FLOAT_EQ(result.z, 10.0f);
    EXPECT_FLOAT_EQ(result.w, 12.0f);
}

TEST(C4QuaternionTest, Subtract) {
    C4Quaternion a(5.0f, 6.0f, 7.0f, 8.0f);
    C4Quaternion b(1.0f, 2.0f, 3.0f, 4.0f);
    C4Quaternion result = a - b;
    EXPECT_FLOAT_EQ(result.x, 4.0f);
    EXPECT_FLOAT_EQ(result.y, 4.0f);
    EXPECT_FLOAT_EQ(result.z, 4.0f);
    EXPECT_FLOAT_EQ(result.w, 4.0f);
}

TEST(C4QuaternionTest, ToMatrixIdentity) {
    C4Quaternion q(0.0f, 0.0f, 0.0f, 1.0f);  // Identity quaternion
    C33Matrix m = q.ToMatrix();
    EXPECT_NEAR(m.a0, 1.0f, 0.001f);
    EXPECT_NEAR(m.a1, 0.0f, 0.001f);
    EXPECT_NEAR(m.a2, 0.0f, 0.001f);
    EXPECT_NEAR(m.b0, 0.0f, 0.001f);
    EXPECT_NEAR(m.b1, 1.0f, 0.001f);
    EXPECT_NEAR(m.b2, 0.0f, 0.001f);
    EXPECT_NEAR(m.c0, 0.0f, 0.001f);
    EXPECT_NEAR(m.c1, 0.0f, 0.001f);
    EXPECT_NEAR(m.c2, 1.0f, 0.001f);
}
