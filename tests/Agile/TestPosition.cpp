#include <gtest/gtest.h>
#include "Agile/Position.h"
#include "Tempest/C3Vector.h"

TEST(PositionTest, DefaultConstructor) {
    Position p;
    EXPECT_FLOAT_EQ(p.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(p.GetY(), 0.0f);
    EXPECT_FLOAT_EQ(p.GetZ(), 0.0f);
}

TEST(PositionTest, ValueConstructor) {
    Position p(1.0f, 2.0f, 3.0f);
    EXPECT_FLOAT_EQ(p.GetX(), 1.0f);
    EXPECT_FLOAT_EQ(p.GetY(), 2.0f);
    EXPECT_FLOAT_EQ(p.GetZ(), 3.0f);
}

TEST(PositionTest, VectorConstructor) {
    Tempest::C3Vector v(4.0f, 5.0f, 6.0f);
    Position p(v);
    EXPECT_FLOAT_EQ(p.GetX(), 4.0f);
    EXPECT_FLOAT_EQ(p.GetY(), 5.0f);
    EXPECT_FLOAT_EQ(p.GetZ(), 6.0f);
}

TEST(PositionTest, CopyConstructor) {
    Position p1(1.0f, 2.0f, 3.0f);
    Position p2(p1);
    EXPECT_FLOAT_EQ(p2.GetX(), 1.0f);
    EXPECT_FLOAT_EQ(p2.GetY(), 2.0f);
    EXPECT_FLOAT_EQ(p2.GetZ(), 3.0f);
}

TEST(PositionTest, AssignmentOperator) {
    Position p1(1.0f, 2.0f, 3.0f);
    Position p2;
    p2 = p1;
    EXPECT_FLOAT_EQ(p2.GetX(), 1.0f);
    EXPECT_FLOAT_EQ(p2.GetY(), 2.0f);
    EXPECT_FLOAT_EQ(p2.GetZ(), 3.0f);
}

TEST(PositionTest, SetPosition) {
    Position p;
    p.SetPosition(1.0f, 2.0f, 3.0f);
    EXPECT_FLOAT_EQ(p.GetX(), 1.0f);
    EXPECT_FLOAT_EQ(p.GetY(), 2.0f);
    EXPECT_FLOAT_EQ(p.GetZ(), 3.0f);
}

TEST(PositionTest, SetPositionVector) {
    Position p;
    Tempest::C3Vector v(4.0f, 5.0f, 6.0f);
    p.SetPosition(v);
    EXPECT_FLOAT_EQ(p.GetX(), 4.0f);
    EXPECT_FLOAT_EQ(p.GetY(), 5.0f);
    EXPECT_FLOAT_EQ(p.GetZ(), 6.0f);
}

TEST(PositionTest, SetIndividualAxes) {
    Position p;
    p.SetX(1.0f);
    p.SetY(2.0f);
    p.SetZ(3.0f);
    EXPECT_FLOAT_EQ(p.GetX(), 1.0f);
    EXPECT_FLOAT_EQ(p.GetY(), 2.0f);
    EXPECT_FLOAT_EQ(p.GetZ(), 3.0f);
}

TEST(PositionTest, GetPosition) {
    Position p(1.0f, 2.0f, 3.0f);
    Tempest::C3Vector v = p.GetPosition();
    EXPECT_FLOAT_EQ(v.x, 1.0f);
    EXPECT_FLOAT_EQ(v.y, 2.0f);
    EXPECT_FLOAT_EQ(v.z, 3.0f);
}

TEST(PositionTest, DistanceTo) {
    Position p1(0.0f, 0.0f, 0.0f);
    Position p2(3.0f, 4.0f, 0.0f);
    EXPECT_FLOAT_EQ(p1.DistanceTo(p2), 5.0f);
}

TEST(PositionTest, DirectionTo) {
    Position p1(0.0f, 0.0f, 0.0f);
    Position p2(3.0f, 4.0f, 0.0f);
    Tempest::C3Vector dir = p1.DirectionTo(p2);
    EXPECT_FLOAT_EQ(dir.x, 3.0f);
    EXPECT_FLOAT_EQ(dir.y, 4.0f);
    EXPECT_FLOAT_EQ(dir.z, 0.0f);
}

TEST(PositionTest, MoveTowards) {
    Position p1(0.0f, 0.0f, 0.0f);
    Position p2(10.0f, 0.0f, 0.0f);
    p1.MoveTowards(p2, 5.0f);
    EXPECT_FLOAT_EQ(p1.GetX(), 5.0f);
    EXPECT_FLOAT_EQ(p1.GetY(), 0.0f);
}

TEST(PositionTest, MoveTowardsOvershoot) {
    Position p1(0.0f, 0.0f, 0.0f);
    Position p2(3.0f, 4.0f, 0.0f);
    p1.MoveTowards(p2, 10.0f);  // Distance is 5, so should snap to target
    EXPECT_FLOAT_EQ(p1.GetX(), 3.0f);
    EXPECT_FLOAT_EQ(p1.GetY(), 4.0f);
}

TEST(PositionTest, Equality) {
    Position p1(1.0f, 2.0f, 3.0f);
    Position p2(1.0f, 2.0f, 3.0f);
    Position p3(4.0f, 5.0f, 6.0f);
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

TEST(PositionTest, Inequality) {
    Position p1(1.0f, 2.0f, 3.0f);
    Position p2(4.0f, 5.0f, 6.0f);
    EXPECT_TRUE(p1 != p2);
}

TEST(PositionTest, AddOffset) {
    Position p1(1.0f, 2.0f, 3.0f);
    Tempest::C3Vector offset(4.0f, 5.0f, 6.0f);
    Position p2 = p1 + offset;
    EXPECT_FLOAT_EQ(p2.GetX(), 5.0f);
    EXPECT_FLOAT_EQ(p2.GetY(), 7.0f);
    EXPECT_FLOAT_EQ(p2.GetZ(), 9.0f);
}

TEST(PositionTest, SubtractOffset) {
    Position p1(5.0f, 7.0f, 9.0f);
    Tempest::C3Vector offset(4.0f, 5.0f, 6.0f);
    Position p2 = p1 - offset;
    EXPECT_FLOAT_EQ(p2.GetX(), 1.0f);
    EXPECT_FLOAT_EQ(p2.GetY(), 2.0f);
    EXPECT_FLOAT_EQ(p2.GetZ(), 3.0f);
}

TEST(PositionTest, IsFacing) {
    Position source(0.0f, 0.0f, 0.0f);
    Position target(10.0f, 10.0f, 10.0f);  // Target is above
    Position reference(10.0f, 0.0f, 0.0f);  // Reference is at same level

    float dot = 0.0f;
    bool facing = Position::IsFacing(source, target, reference, &dot);
    EXPECT_TRUE(facing);
    EXPECT_GT(dot, 0.0f);
}

TEST(PositionTest, IsFacingBehind) {
    Position source(0.0f, 0.0f, 0.0f);
    Position target(-10.0f, -10.0f, -10.0f);  // Target is below and behind
    Position reference(10.0f, 0.0f, 0.0f);  // Reference is in front

    float dot = 0.0f;
    bool facing = Position::IsFacing(source, target, reference, &dot);
    EXPECT_FALSE(facing);
}
