#include <gtest/gtest.h>
#include "Tempest/CRect.h"
#include "Tempest/C2Vector.h"
#include <cmath>

using namespace Tempest;

TEST(CRectTest, DefaultConstructor) {
    CRect r;
    EXPECT_FLOAT_EQ(r.minX, 0.0f);
    EXPECT_FLOAT_EQ(r.minY, 0.0f);
    EXPECT_FLOAT_EQ(r.maxX, 0.0f);
    EXPECT_FLOAT_EQ(r.maxY, 0.0f);
}

TEST(CRectTest, ParameterizedConstructor) {
    CRect r(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_FLOAT_EQ(r.minY, 1.0f);
    EXPECT_FLOAT_EQ(r.minX, 2.0f);
    EXPECT_FLOAT_EQ(r.maxY, 3.0f);
    EXPECT_FLOAT_EQ(r.maxX, 4.0f);
}

TEST(CRectTest, Equality) {
    CRect a(1.0f, 2.0f, 3.0f, 4.0f);
    CRect b(1.0f, 2.0f, 3.0f, 4.0f);
    CRect c(5.0f, 6.0f, 7.0f, 8.0f);
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
}

TEST(CRectTest, Inequality) {
    CRect a(1.0f, 2.0f, 3.0f, 4.0f);
    CRect b(5.0f, 6.0f, 7.0f, 8.0f);
    EXPECT_TRUE(a != b);
}

TEST(CRectTest, Width) {
    CRect r(0.0f, 0.0f, 0.0f, 10.0f);
    EXPECT_FLOAT_EQ(r.Width(), 10.0f);
}

TEST(CRectTest, Height) {
    CRect r(0.0f, 0.0f, 5.0f, 0.0f);
    EXPECT_FLOAT_EQ(r.Height(), 5.0f);
}

TEST(CRectTest, IsPointInside) {
    CRect r(0.0f, 0.0f, 10.0f, 10.0f);
    C2Vector inside(5.0f, 5.0f);
    C2Vector outside(15.0f, 15.0f);
    EXPECT_TRUE(r.IsPointInside(inside));
    EXPECT_FALSE(r.IsPointInside(outside));
}

TEST(CRectTest, ContainsPoint) {
    CRect r(0.0f, 0.0f, 10.0f, 10.0f);
    C2Vector inside(5.0f, 5.0f);
    C2Vector outside(15.0f, 15.0f);
    EXPECT_TRUE(r.Contains(inside));
    EXPECT_FALSE(r.Contains(outside));
}

TEST(CRectTest, ContainsRect) {
    CRect outer(0.0f, 0.0f, 10.0f, 10.0f);
    CRect inner(2.0f, 2.0f, 8.0f, 8.0f);
    CRect overlapping(5.0f, 5.0f, 15.0f, 15.0f);
    EXPECT_TRUE(outer.Contains(inner));
    EXPECT_FALSE(outer.Contains(overlapping));
}

TEST(CRectTest, Intersection) {
    CRect a(0.0f, 0.0f, 10.0f, 10.0f);
    CRect b(5.0f, 5.0f, 15.0f, 15.0f);
    CRect i = CRect::Intersection(a, b);
    EXPECT_FLOAT_EQ(i.minX, 5.0f);
    EXPECT_FLOAT_EQ(i.minY, 5.0f);
    EXPECT_FLOAT_EQ(i.maxX, 10.0f);
    EXPECT_FLOAT_EQ(i.maxY, 10.0f);
}

TEST(CRectTest, Union) {
    CRect a(0.0f, 0.0f, 5.0f, 5.0f);
    CRect b(3.0f, 3.0f, 10.0f, 10.0f);
    CRect u = CRect::Union(a, b);
    EXPECT_FLOAT_EQ(u.minX, 0.0f);
    EXPECT_FLOAT_EQ(u.minY, 0.0f);
    EXPECT_FLOAT_EQ(u.maxX, 10.0f);
    EXPECT_FLOAT_EQ(u.maxY, 10.0f);
}

TEST(CRectTest, ExpandPoint) {
    CRect r(2.0f, 2.0f, 8.0f, 8.0f);
    C2Vector pt(10.0f, 10.0f);
    r.Expand(pt);
    EXPECT_FLOAT_EQ(r.maxX, 10.0f);
    EXPECT_FLOAT_EQ(r.maxY, 10.0f);
}

TEST(CRectTest, ExpandRect) {
    CRect r(2.0f, 2.0f, 8.0f, 8.0f);
    CRect expand(0.0f, 0.0f, 10.0f, 10.0f);
    r.Expand(expand);
    EXPECT_FLOAT_EQ(r.minX, 0.0f);
    EXPECT_FLOAT_EQ(r.minY, 0.0f);
    EXPECT_FLOAT_EQ(r.maxX, 10.0f);
    EXPECT_FLOAT_EQ(r.maxY, 10.0f);
}

TEST(CRectTest, Center) {
    CRect r(0.0f, 0.0f, 10.0f, 10.0f);
    C2Vector center = r.Center();
    EXPECT_FLOAT_EQ(center.x, 5.0f);
    EXPECT_FLOAT_EQ(center.y, 5.0f);
}

TEST(CRectTest, Clamp) {
    CRect r(0.0f, 0.0f, 10.0f, 10.0f);
    C2Vector pt(15.0f, 15.0f);
    r.Clamp(pt);
    EXPECT_FLOAT_EQ(pt.x, 10.0f);
    EXPECT_FLOAT_EQ(pt.y, 10.0f);
}
