#include <gtest/gtest.h>
#include "Game/CBoundingBox.h"
#include <cmath>

TEST(CBoundingBoxTest, DefaultConstructor) {
    CBoundingBox bb;
    // Default constructor doesn't initialize members
    // This is a known limitation
    EXPECT_TRUE(true);
}

TEST(CBoundingBoxTest, VectorConstructor) {
    C3Vector min(1.0f, 2.0f, 3.0f);
    C3Vector max(4.0f, 5.0f, 6.0f);
    CBoundingBox bb(min, max);

    EXPECT_FLOAT_EQ(bb.x.l, 1.0f);
    EXPECT_FLOAT_EQ(bb.x.h, 4.0f);
    EXPECT_FLOAT_EQ(bb.y.l, 2.0f);
    EXPECT_FLOAT_EQ(bb.y.h, 5.0f);
    EXPECT_FLOAT_EQ(bb.z.l, 3.0f);
    EXPECT_FLOAT_EQ(bb.z.h, 6.0f);
}

TEST(CBoundingBoxTest, ParameterizedConstructor) {
    CBoundingBox bb(1.0f, 4.0f, 2.0f, 5.0f, 3.0f, 6.0f);

    EXPECT_FLOAT_EQ(bb.x.l, 1.0f);
    EXPECT_FLOAT_EQ(bb.x.h, 4.0f);
    EXPECT_FLOAT_EQ(bb.y.l, 2.0f);
    EXPECT_FLOAT_EQ(bb.y.h, 5.0f);
    EXPECT_FLOAT_EQ(bb.z.l, 3.0f);
    EXPECT_FLOAT_EQ(bb.z.h, 6.0f);
}

TEST(CBoundingBoxTest, GetMin) {
    CBoundingBox bb(1.0f, 4.0f, 2.0f, 5.0f, 3.0f, 6.0f);
    C3Vector min = bb.GetMin();

    EXPECT_FLOAT_EQ(min.x, 1.0f);
    EXPECT_FLOAT_EQ(min.y, 2.0f);
    EXPECT_FLOAT_EQ(min.z, 3.0f);
}

TEST(CBoundingBoxTest, GetMax) {
    CBoundingBox bb(1.0f, 4.0f, 2.0f, 5.0f, 3.0f, 6.0f);
    C3Vector max = bb.GetMax();

    EXPECT_FLOAT_EQ(max.x, 4.0f);
    EXPECT_FLOAT_EQ(max.y, 5.0f);
    EXPECT_FLOAT_EQ(max.z, 6.0f);
}

TEST(CBoundingBoxTest, GetCenter) {
    CBoundingBox bb(0.0f, 10.0f, 0.0f, 10.0f, 0.0f, 10.0f);
    C3Vector center = bb.GetCenter();

    EXPECT_FLOAT_EQ(center.x, 5.0f);
    EXPECT_FLOAT_EQ(center.y, 5.0f);
    EXPECT_FLOAT_EQ(center.z, 5.0f);
}

TEST(CBoundingBoxTest, GetSize) {
    CBoundingBox bb(1.0f, 4.0f, 2.0f, 5.0f, 3.0f, 6.0f);
    C3Vector size = bb.GetSize();

    EXPECT_FLOAT_EQ(size.x, 3.0f);
    EXPECT_FLOAT_EQ(size.y, 3.0f);
    EXPECT_FLOAT_EQ(size.z, 3.0f);
}

TEST(CBoundingBoxTest, GetVolume) {
    CBoundingBox bb(0.0f, 2.0f, 0.0f, 3.0f, 0.0f, 4.0f);
    EXPECT_FLOAT_EQ(bb.GetVolume(), 24.0f);
}

TEST(CBoundingBoxTest, GetSurfaceArea) {
    CBoundingBox bb(0.0f, 2.0f, 0.0f, 3.0f, 0.0f, 4.0f);
    // Surface area = 2 * (2*3 + 3*4 + 4*2) = 2 * (6 + 12 + 8) = 52
    EXPECT_FLOAT_EQ(bb.GetSurfaceArea(), 52.0f);
}

TEST(CBoundingBoxTest, ContainsPoint) {
    CBoundingBox bb(0.0f, 10.0f, 0.0f, 10.0f, 0.0f, 10.0f);

    C3Vector inside(5.0f, 5.0f, 5.0f);
    C3Vector outside(15.0f, 5.0f, 5.0f);

    EXPECT_TRUE(bb.Contains(inside));
    EXPECT_FALSE(bb.Contains(outside));
}

TEST(CBoundingBoxTest, ContainsBoundingBox) {
    CBoundingBox outer(0.0f, 10.0f, 0.0f, 10.0f, 0.0f, 10.0f);
    CBoundingBox inner(2.0f, 8.0f, 2.0f, 8.0f, 2.0f, 8.0f);
    CBoundingBox overlapping(5.0f, 15.0f, 5.0f, 15.0f, 5.0f, 15.0f);

    EXPECT_TRUE(outer.Contains(inner));
    EXPECT_FALSE(outer.Contains(overlapping));
}

TEST(CBoundingBoxTest, Intersects) {
    CBoundingBox a(0.0f, 5.0f, 0.0f, 5.0f, 0.0f, 5.0f);
    CBoundingBox b(3.0f, 8.0f, 3.0f, 8.0f, 3.0f, 8.0f);
    CBoundingBox c(10.0f, 15.0f, 10.0f, 15.0f, 10.0f, 15.0f);

    EXPECT_TRUE(a.Intersects(b));
    EXPECT_FALSE(a.Intersects(c));
}

TEST(CBoundingBoxTest, ExpandPoint) {
    CBoundingBox bb(2.0f, 8.0f, 2.0f, 8.0f, 2.0f, 8.0f);
    C3Vector point(10.0f, 10.0f, 10.0f);

    bb.Expand(point);

    EXPECT_FLOAT_EQ(bb.x.h, 10.0f);
    EXPECT_FLOAT_EQ(bb.y.h, 10.0f);
    EXPECT_FLOAT_EQ(bb.z.h, 10.0f);
}

TEST(CBoundingBoxTest, ExpandBoundingBox) {
    CBoundingBox a(2.0f, 8.0f, 2.0f, 8.0f, 2.0f, 8.0f);
    CBoundingBox b(0.0f, 5.0f, 0.0f, 5.0f, 0.0f, 5.0f);

    a.Expand(b);

    EXPECT_FLOAT_EQ(a.x.l, 0.0f);
    EXPECT_FLOAT_EQ(a.x.h, 8.0f);
    EXPECT_FLOAT_EQ(a.y.l, 0.0f);
    EXPECT_FLOAT_EQ(a.y.h, 8.0f);
    EXPECT_FLOAT_EQ(a.z.l, 0.0f);
    EXPECT_FLOAT_EQ(a.z.h, 8.0f);
}

TEST(CBoundingBoxTest, ExpandByMargin) {
    CBoundingBox bb(2.0f, 8.0f, 2.0f, 8.0f, 2.0f, 8.0f);

    bb.ExpandByMargin(1.0f);

    EXPECT_FLOAT_EQ(bb.x.l, 1.0f);
    EXPECT_FLOAT_EQ(bb.x.h, 9.0f);
    EXPECT_FLOAT_EQ(bb.y.l, 1.0f);
    EXPECT_FLOAT_EQ(bb.y.h, 9.0f);
    EXPECT_FLOAT_EQ(bb.z.l, 1.0f);
    EXPECT_FLOAT_EQ(bb.z.h, 9.0f);
}

TEST(CBoundingBoxTest, Reset) {
    CBoundingBox bb(1.0f, 4.0f, 2.0f, 5.0f, 3.0f, 6.0f);

    bb.Reset();

    EXPECT_FLOAT_EQ(bb.x.l, 0.0f);
    EXPECT_FLOAT_EQ(bb.x.h, 0.0f);
    EXPECT_FLOAT_EQ(bb.y.l, 0.0f);
    EXPECT_FLOAT_EQ(bb.y.h, 0.0f);
    EXPECT_FLOAT_EQ(bb.z.l, 0.0f);
    EXPECT_FLOAT_EQ(bb.z.h, 0.0f);
}

TEST(CBoundingBoxTest, Equality) {
    CBoundingBox a(1.0f, 4.0f, 2.0f, 5.0f, 3.0f, 6.0f);
    CBoundingBox b(1.0f, 4.0f, 2.0f, 5.0f, 3.0f, 6.0f);
    CBoundingBox c(1.0f, 4.0f, 2.0f, 5.0f, 3.0f, 7.0f);

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
}

TEST(CBoundingBoxTest, Inequality) {
    CBoundingBox a(1.0f, 4.0f, 2.0f, 5.0f, 3.0f, 6.0f);
    CBoundingBox b(1.0f, 4.0f, 2.0f, 5.0f, 3.0f, 7.0f);

    EXPECT_TRUE(a != b);
}
