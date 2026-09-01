#include <gtest/gtest.h>
#include <cmath>
#include "Agile/CAngle.h"
#include "Agile/SmartPosition.h"
#include "Agile/RangeListener.h"
#include "Agile/MovementModifier.h"
#include "Agile/ProjectilePosition.h"

// Test CAngle
TEST(CAngleTest, DefaultConstructor) {
    CAngle angle;
    // Verify construction doesn't crash
}

TEST(CAngleTest, ValueConstructor) {
    CAngle angle(M_PI / 4.0f);
    EXPECT_NEAR(angle.GetRadians(), M_PI / 4.0f, 0.001f);
}

TEST(CAngleTest, SetAngle) {
    CAngle angle;
    angle.Set_(M_PI / 2.0f);
    EXPECT_NEAR(angle.GetRadians(), M_PI / 2.0f, 0.001f);
}

TEST(CAngleTest, NormalizeAngle) {
    CAngle angle;
    angle.Set_(3.0f * M_PI);  // Should normalize to PI
    EXPECT_NEAR(angle.GetRadians(), M_PI, 0.001f);
}

TEST(CAngleTest, NegativeAngle) {
    CAngle angle;
    angle.Set_(-M_PI / 2.0f);  // Should normalize to 3*PI/2
    EXPECT_NEAR(angle.GetRadians(), 3.0f * M_PI / 2.0f, 0.001f);
}

TEST(CAngleTest, CalcSinCos) {
    CAngle angle(M_PI / 4.0f);
    EXPECT_NEAR(angle.GetSin(), std::sin(M_PI / 4.0f), 0.001f);
    EXPECT_NEAR(angle.GetCos(), std::cos(M_PI / 4.0f), 0.001f);
}

TEST(CAngleTest, GetDegrees) {
    CAngle angle(M_PI);
    EXPECT_NEAR(angle.GetDegrees(), 180.0f, 0.001f);
}

// Test SmartPosition
TEST(SmartPositionTest, DefaultConstructor) {
    SmartPosition pos;
    EXPECT_FALSE(pos.IsValid());
    EXPECT_EQ(pos.GetRegionIndex(), -1);
}

TEST(SmartPositionTest, SetRegionIndex) {
    SmartPosition pos;
    pos.SetRegionIndex(42);
    EXPECT_TRUE(pos.IsValid());
    EXPECT_EQ(pos.GetRegionIndex(), 42);
}

// Test RangeListener
TEST(RangeListenerTest, DefaultConstructor) {
    RangeListener listener;
    EXPECT_FLOAT_EQ(listener.GetRange(), 0.0f);
}

TEST(RangeListenerTest, SetRange) {
    RangeListener listener;
    listener.SetRange(100.0f);
    EXPECT_FLOAT_EQ(listener.GetRange(), 100.0f);
}

// Test MovementModifier
TEST(MovementModifierTest, DefaultConstructor) {
    MovementModifier modifier;
    EXPECT_FLOAT_EQ(modifier.GetSpeedMultiplier(), 1.0f);
    EXPECT_FLOAT_EQ(modifier.GetAcceleration(), 0.0f);
}

TEST(MovementModifierTest, SetSpeedMultiplier) {
    MovementModifier modifier;
    modifier.SetSpeedMultiplier(2.0f);
    EXPECT_FLOAT_EQ(modifier.GetSpeedMultiplier(), 2.0f);
}

TEST(MovementModifierTest, SetAcceleration) {
    MovementModifier modifier;
    modifier.SetAcceleration(10.0f);
    EXPECT_FLOAT_EQ(modifier.GetAcceleration(), 10.0f);
}

// Test ProjectilePosition
TEST(ProjectilePositionTest, DefaultConstructor) {
    ProjectilePosition pos;
    // Verify construction doesn't crash
}

TEST(ProjectilePositionTest, SetPosition) {
    ProjectilePosition pos;
    Tempest::C3Vector position(1.0f, 2.0f, 3.0f);
    pos.Set(position);
    EXPECT_FLOAT_EQ(pos.GetPosition().x, 1.0f);
    EXPECT_FLOAT_EQ(pos.GetPosition().y, 2.0f);
    EXPECT_FLOAT_EQ(pos.GetPosition().z, 3.0f);
}

TEST(ProjectilePositionTest, SetVelocity) {
    ProjectilePosition pos;
    Tempest::C3Vector velocity(1.0f, 0.0f, 0.0f);
    pos.SetVelocity(velocity);
    EXPECT_FLOAT_EQ(pos.GetVelocity().x, 1.0f);
}

TEST(ProjectilePositionTest, Update) {
    ProjectilePosition pos;
    pos.Set(Tempest::C3Vector(0.0f, 0.0f, 0.0f));
    pos.SetVelocity(Tempest::C3Vector(1.0f, 0.0f, 0.0f));

    pos.Update(1.0f);

    EXPECT_NEAR(pos.GetPosition().x, 1.0f, 0.001f);
}

TEST(ProjectilePositionTest, HasReachedTarget) {
    ProjectilePosition pos;
    pos.Set(Tempest::C3Vector(0.0f, 0.0f, 0.0f));
    pos.SetTarget(Tempest::C3Vector(0.1f, 0.0f, 0.0f));

    EXPECT_FALSE(pos.HasReachedTarget());

    pos.Set(Tempest::C3Vector(0.05f, 0.0f, 0.0f));
    EXPECT_TRUE(pos.HasReachedTarget());
}
