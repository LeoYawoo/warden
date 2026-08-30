#include <gtest/gtest.h>
#include "NTempest/C44Matrix.h"
#include "NTempest/C3Vector.h"
#include <cmath>

using namespace NTempest;

TEST(C44MatrixTest, DefaultConstructor) {
    C44Matrix m;
    EXPECT_FLOAT_EQ(m.a0, 1.0f);
    EXPECT_FLOAT_EQ(m.b1, 1.0f);
    EXPECT_FLOAT_EQ(m.c2, 1.0f);
    EXPECT_FLOAT_EQ(m.d3, 1.0f);
}

TEST(C44MatrixTest, Identity) {
    C44Matrix m = C44Matrix::Identity();
    EXPECT_FLOAT_EQ(m.a0, 1.0f);
    EXPECT_FLOAT_EQ(m.b1, 1.0f);
    EXPECT_FLOAT_EQ(m.c2, 1.0f);
    EXPECT_FLOAT_EQ(m.d3, 1.0f);
}

TEST(C44MatrixTest, RotationAroundZ) {
    float angle = 3.1415927f / 2.0f;  // 90 degrees
    C44Matrix m = C44Matrix::RotationAroundZ(angle);
    EXPECT_NEAR(m.a0, 0.0f, 0.001f);
    EXPECT_NEAR(m.a1, 1.0f, 0.001f);
    EXPECT_NEAR(m.b0, -1.0f, 0.001f);
    EXPECT_NEAR(m.b1, 0.0f, 0.001f);
}

TEST(C44MatrixTest, RotationAroundX) {
    float angle = 3.1415927f / 2.0f;  // 90 degrees
    C44Matrix m = C44Matrix::RotationAroundX(angle);
    EXPECT_NEAR(m.a0, 1.0f, 0.001f);
    EXPECT_NEAR(m.b1, 0.0f, 0.001f);
    EXPECT_NEAR(m.b2, 1.0f, 0.001f);
    EXPECT_NEAR(m.c1, -1.0f, 0.001f);
    EXPECT_NEAR(m.c2, 0.0f, 0.001f);
}

TEST(C44MatrixTest, RotationAroundY) {
    float angle = 3.1415927f / 2.0f;  // 90 degrees
    C44Matrix m = C44Matrix::RotationAroundY(angle);
    EXPECT_NEAR(m.a0, 0.0f, 0.001f);
    EXPECT_NEAR(m.a2, -1.0f, 0.001f);
    EXPECT_NEAR(m.c0, 1.0f, 0.001f);
    EXPECT_NEAR(m.c2, 0.0f, 0.001f);
}

TEST(C44MatrixTest, Determinant) {
    C44Matrix m;
    EXPECT_NEAR(m.Determinant(), 1.0f, 0.001f);
}

TEST(C44MatrixTest, Transpose) {
    C44Matrix m(1.0f, 2.0f, 3.0f, 4.0f,
                5.0f, 6.0f, 7.0f, 8.0f,
                9.0f, 10.0f, 11.0f, 12.0f,
                13.0f, 14.0f, 15.0f, 16.0f);
    C44Matrix t = m.Transpose();
    EXPECT_FLOAT_EQ(t.a0, 1.0f);
    EXPECT_FLOAT_EQ(t.a1, 5.0f);
    EXPECT_FLOAT_EQ(t.a2, 9.0f);
    EXPECT_FLOAT_EQ(t.a3, 13.0f);
    EXPECT_FLOAT_EQ(t.b0, 2.0f);
    EXPECT_FLOAT_EQ(t.b1, 6.0f);
}

TEST(C44MatrixTest, MultiplyScalar) {
    C44Matrix m(1.0f, 2.0f, 3.0f, 4.0f,
                5.0f, 6.0f, 7.0f, 8.0f,
                9.0f, 10.0f, 11.0f, 12.0f,
                13.0f, 14.0f, 15.0f, 16.0f);
    C44Matrix result = m * 2.0f;
    EXPECT_FLOAT_EQ(result.a0, 2.0f);
    EXPECT_FLOAT_EQ(result.d3, 32.0f);
}

TEST(C44MatrixTest, MultiplyMatrix) {
    C44Matrix a = C44Matrix::Identity();
    C44Matrix b(1.0f, 2.0f, 3.0f, 4.0f,
                5.0f, 6.0f, 7.0f, 8.0f,
                9.0f, 10.0f, 11.0f, 12.0f,
                13.0f, 14.0f, 15.0f, 16.0f);
    C44Matrix c = a * b;
    EXPECT_FLOAT_EQ(c.a0, 1.0f);
    EXPECT_FLOAT_EQ(c.d3, 16.0f);
}

TEST(C44MatrixTest, Translate) {
    C44Matrix m;
    C3Vector move(1.0f, 2.0f, 3.0f);
    m.Translate(move);
    EXPECT_FLOAT_EQ(m.d0, 1.0f);
    EXPECT_FLOAT_EQ(m.d1, 2.0f);
    EXPECT_FLOAT_EQ(m.d2, 3.0f);
}

TEST(C44MatrixTest, ScaleVector) {
    C44Matrix m;
    C3Vector scale(2.0f, 3.0f, 4.0f);
    m.Scale(scale);
    EXPECT_FLOAT_EQ(m.a0, 2.0f);
    EXPECT_FLOAT_EQ(m.b1, 3.0f);
    EXPECT_FLOAT_EQ(m.c2, 4.0f);
}

TEST(C44MatrixTest, ScaleUniform) {
    C44Matrix m;
    m.Scale(2.0f);
    EXPECT_FLOAT_EQ(m.a0, 2.0f);
    EXPECT_FLOAT_EQ(m.b1, 2.0f);
    EXPECT_FLOAT_EQ(m.c2, 2.0f);
}

TEST(C44MatrixTest, Perspective) {
    float fov = 3.1415927f / 4.0f;  // 45 degrees
    float aspect = 16.0f / 9.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
    C44Matrix m = C44Matrix::Perspective(fov, aspect, nearPlane, farPlane);
    EXPECT_NEAR(m.a0, 1.0f / (aspect * tanf(fov * 0.5f)), 0.001f);
    EXPECT_NEAR(m.b1, 1.0f / tanf(fov * 0.5f), 0.001f);
}

TEST(C44MatrixTest, Orthographic) {
    C44Matrix m = C44Matrix::Orthographic(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
    EXPECT_NEAR(m.a0, 1.0f, 0.001f);
    EXPECT_NEAR(m.b1, 1.0f, 0.001f);
}
