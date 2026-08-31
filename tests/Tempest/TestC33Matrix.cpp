#include <gtest/gtest.h>
#include "Tempest/C33Matrix.h"
#include "Tempest/C3Vector.h"
#include <cmath>

using namespace Tempest;

TEST(C33MatrixTest, DefaultConstructor) {
    C33Matrix m;
    EXPECT_FLOAT_EQ(m.a0, 1.0f);
    EXPECT_FLOAT_EQ(m.a1, 0.0f);
    EXPECT_FLOAT_EQ(m.a2, 0.0f);
    EXPECT_FLOAT_EQ(m.b0, 0.0f);
    EXPECT_FLOAT_EQ(m.b1, 1.0f);
    EXPECT_FLOAT_EQ(m.b2, 0.0f);
    EXPECT_FLOAT_EQ(m.c0, 0.0f);
    EXPECT_FLOAT_EQ(m.c1, 0.0f);
    EXPECT_FLOAT_EQ(m.c2, 1.0f);
}

TEST(C33MatrixTest, Identity) {
    C33Matrix m = C33Matrix::Identity();
    EXPECT_FLOAT_EQ(m.a0, 1.0f);
    EXPECT_FLOAT_EQ(m.b1, 1.0f);
    EXPECT_FLOAT_EQ(m.c2, 1.0f);
}

TEST(C33MatrixTest, Determinant) {
    C33Matrix m(1.0f, 2.0f, 3.0f,
                4.0f, 5.0f, 6.0f,
                7.0f, 8.0f, 9.0f);
    EXPECT_NEAR(m.Determinant(), 0.0f, 0.001f);
}

TEST(C33MatrixTest, DeterminantNonZero) {
    C33Matrix m(1.0f, 0.0f, 0.0f,
                0.0f, 2.0f, 0.0f,
                0.0f, 0.0f, 3.0f);
    EXPECT_NEAR(m.Determinant(), 6.0f, 0.001f);
}

TEST(C33MatrixTest, Transpose) {
    C33Matrix m(1.0f, 2.0f, 3.0f,
                4.0f, 5.0f, 6.0f,
                7.0f, 8.0f, 9.0f);
    C33Matrix t = m.Transpose();
    EXPECT_FLOAT_EQ(t.a0, 1.0f);
    EXPECT_FLOAT_EQ(t.a1, 4.0f);
    EXPECT_FLOAT_EQ(t.a2, 7.0f);
    EXPECT_FLOAT_EQ(t.b0, 2.0f);
    EXPECT_FLOAT_EQ(t.b1, 5.0f);
    EXPECT_FLOAT_EQ(t.b2, 8.0f);
    EXPECT_FLOAT_EQ(t.c0, 3.0f);
    EXPECT_FLOAT_EQ(t.c1, 6.0f);
    EXPECT_FLOAT_EQ(t.c2, 9.0f);
}

TEST(C33MatrixTest, MultiplyScalar) {
    C33Matrix m(1.0f, 2.0f, 3.0f,
                4.0f, 5.0f, 6.0f,
                7.0f, 8.0f, 9.0f);
    C33Matrix result = m * 2.0f;
    EXPECT_FLOAT_EQ(result.a0, 2.0f);
    EXPECT_FLOAT_EQ(result.a1, 4.0f);
    EXPECT_FLOAT_EQ(result.a2, 6.0f);
    EXPECT_FLOAT_EQ(result.b0, 8.0f);
    EXPECT_FLOAT_EQ(result.b1, 10.0f);
    EXPECT_FLOAT_EQ(result.b2, 12.0f);
    EXPECT_FLOAT_EQ(result.c0, 14.0f);
    EXPECT_FLOAT_EQ(result.c1, 16.0f);
    EXPECT_FLOAT_EQ(result.c2, 18.0f);
}

TEST(C33MatrixTest, MultiplyMatrix) {
    C33Matrix a(1.0f, 2.0f, 3.0f,
                4.0f, 5.0f, 6.0f,
                7.0f, 8.0f, 9.0f);
    C33Matrix b(9.0f, 8.0f, 7.0f,
                6.0f, 5.0f, 4.0f,
                3.0f, 2.0f, 1.0f);
    C33Matrix c = a * b;
    EXPECT_NEAR(c.a0, 30.0f, 0.001f);
    EXPECT_NEAR(c.a1, 24.0f, 0.001f);
    EXPECT_NEAR(c.a2, 18.0f, 0.001f);
    EXPECT_NEAR(c.b0, 84.0f, 0.001f);
    EXPECT_NEAR(c.b1, 69.0f, 0.001f);
    EXPECT_NEAR(c.b2, 54.0f, 0.001f);
    EXPECT_NEAR(c.c0, 138.0f, 0.001f);
    EXPECT_NEAR(c.c1, 114.0f, 0.001f);
    EXPECT_NEAR(c.c2, 90.0f, 0.001f);
}

TEST(C33MatrixTest, MultiplyVector) {
    C33Matrix m(1.0f, 0.0f, 0.0f,
                0.0f, 2.0f, 0.0f,
                0.0f, 0.0f, 3.0f);
    C3Vector v(1.0f, 1.0f, 1.0f);
    C3Vector result = m * v;
    EXPECT_FLOAT_EQ(result.x, 1.0f);
    EXPECT_FLOAT_EQ(result.y, 2.0f);
    EXPECT_FLOAT_EQ(result.z, 3.0f);
}

TEST(C33MatrixTest, Adjoint) {
    C33Matrix m(1.0f, 2.0f, 3.0f,
                0.0f, 1.0f, 4.0f,
                5.0f, 6.0f, 0.0f);
    C33Matrix adj = m.Adjoint();
    float det = m.Determinant();
    C33Matrix product = m * adj;
    EXPECT_NEAR(product.a0, det, 0.001f);
    EXPECT_NEAR(product.b1, det, 0.001f);
    EXPECT_NEAR(product.c2, det, 0.001f);
}
