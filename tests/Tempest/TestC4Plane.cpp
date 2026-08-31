#include <gtest/gtest.h>
#include "Tempest/C4Plane.h"
#include "Tempest/C3Vector.h"
#include <cmath>

using namespace Tempest;

TEST(C4PlaneTest, DefaultConstructor) {
    C4Plane p;
    C3Vector normal = p.GetNormal();
    EXPECT_FLOAT_EQ(normal.x, 0.0f);
    EXPECT_FLOAT_EQ(normal.y, 0.0f);
    EXPECT_FLOAT_EQ(normal.z, 0.0f);
    EXPECT_FLOAT_EQ(p.GetDistance(), 0.0f);
}

TEST(C4PlaneTest, NormalDistanceConstructor) {
    C3Vector normal(0.0f, 1.0f, 0.0f);
    float distance = -5.0f;
    C4Plane p(normal, distance);
    C3Vector n = p.GetNormal();
    EXPECT_FLOAT_EQ(n.x, 0.0f);
    EXPECT_FLOAT_EQ(n.y, 1.0f);
    EXPECT_FLOAT_EQ(n.z, 0.0f);
    EXPECT_FLOAT_EQ(p.GetDistance(), -5.0f);
}

TEST(C4PlaneTest, From3Pos) {
    C3Vector p1(0.0f, 0.0f, 0.0f);
    C3Vector p2(1.0f, 0.0f, 0.0f);
    C3Vector p3(0.0f, 1.0f, 0.0f);
    C4Plane plane(p1, p2, p3);
    C3Vector normal = plane.GetNormal();
    EXPECT_NEAR(normal.z, 1.0f, 0.001f);
    EXPECT_NEAR(normal.x, 0.0f, 0.001f);
    EXPECT_NEAR(normal.y, 0.0f, 0.001f);
}

TEST(C4PlaneTest, Dot) {
    C3Vector normal(0.0f, 1.0f, 0.0f);
    float distance = -5.0f;
    C4Plane p(normal, distance);
    C3Vector point(0.0f, 5.0f, 0.0f);
    EXPECT_NEAR(p.Dot(point), 0.0f, 0.001f);
}

TEST(C4PlaneTest, Distance) {
    C3Vector normal(0.0f, 1.0f, 0.0f);
    float distance = 0.0f;
    C4Plane p(normal, distance);
    C3Vector point(0.0f, 5.0f, 0.0f);
    EXPECT_NEAR(p.Distance(point), 5.0f, 0.001f);
}

TEST(C4PlaneTest, Normalize) {
    C3Vector normal(0.0f, 2.0f, 0.0f);
    float distance = -10.0f;
    C4Plane p(normal, distance);
    p.Normalize();
    C3Vector n = p.GetNormal();
    EXPECT_NEAR(n.Mag(), 1.0f, 0.001f);
    EXPECT_NEAR(p.GetDistance(), -5.0f, 0.001f);
}
