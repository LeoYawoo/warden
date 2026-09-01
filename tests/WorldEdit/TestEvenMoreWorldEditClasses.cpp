#include <gtest/gtest.h>
#include "WorldEdit/CWorldObjects.h"
#include "WorldEdit/CWeatherEffects.h"
#include "WorldEdit/TextureUtilities.h"

// Test CWorldObjects
TEST(CWorldObjectsTest, DefaultConstructor) {
    CWorldObjects obj;
    EXPECT_EQ(obj.GetObjectId(), 0);
    EXPECT_EQ(obj.GetObjectType(), 0);
    EXPECT_TRUE(obj.IsVisible());
    EXPECT_TRUE(obj.IsSelectable());
}

TEST(CWorldObjectsTest, SetObjectId) {
    CWorldObjects obj;
    obj.SetObjectId(42);
    EXPECT_EQ(obj.GetObjectId(), 42);
}

TEST(CWorldObjectsTest, SetObjectName) {
    CWorldObjects obj;
    obj.SetObjectName("Tree");
    EXPECT_STREQ(obj.GetObjectName(), "Tree");
}

TEST(CWorldObjectsTest, SetObjectType) {
    CWorldObjects obj;
    obj.SetObjectType(3);
    EXPECT_EQ(obj.GetObjectType(), 3);
}

TEST(CWorldObjectsTest, SetPosition) {
    CWorldObjects obj;
    obj.SetPosition(10.0f, 20.0f, 30.0f);
    EXPECT_FLOAT_EQ(obj.GetX(), 10.0f);
    EXPECT_FLOAT_EQ(obj.GetY(), 20.0f);
    EXPECT_FLOAT_EQ(obj.GetZ(), 30.0f);
}

TEST(CWorldObjectsTest, SetRotation) {
    CWorldObjects obj;
    obj.SetRotation(45.0f);
    EXPECT_FLOAT_EQ(obj.GetRotation(), 45.0f);
}

TEST(CWorldObjectsTest, SetScale) {
    CWorldObjects obj;
    obj.SetScale(2.0f, 3.0f, 4.0f);
    EXPECT_FLOAT_EQ(obj.GetScaleX(), 2.0f);
    EXPECT_FLOAT_EQ(obj.GetScaleY(), 3.0f);
    EXPECT_FLOAT_EQ(obj.GetScaleZ(), 4.0f);
}

TEST(CWorldObjectsTest, SetVisible) {
    CWorldObjects obj;
    obj.SetVisible(false);
    EXPECT_FALSE(obj.IsVisible());
}

TEST(CWorldObjectsTest, SetSelectable) {
    CWorldObjects obj;
    obj.SetSelectable(false);
    EXPECT_FALSE(obj.IsSelectable());
}

TEST(CWorldObjectsTest, SetLifetime) {
    CWorldObjects obj;
    obj.SetLifetime(10.0f);
    EXPECT_FLOAT_EQ(obj.GetLifetime(), 10.0f);
    EXPECT_FALSE(obj.HasExpired());
}

TEST(CWorldObjectsTest, HasExpired) {
    CWorldObjects obj;
    obj.SetLifetime(0.0f);
    EXPECT_FALSE(obj.HasExpired());
}

// Test CWeatherEffects
TEST(CWeatherEffectsTest, DefaultConstructor) {
    CWeatherEffects effects;
    EXPECT_EQ(effects.GetEffectsId(), 0);
    EXPECT_FALSE(effects.IsEnabled());
    EXPECT_FALSE(effects.IsPlaying());
    EXPECT_EQ(effects.GetAreaCount(), 0u);
    EXPECT_EQ(effects.GetEmitterCount(), 0u);
}

TEST(CWeatherEffectsTest, SetEffectsId) {
    CWeatherEffects effects;
    effects.SetEffectsId(10);
    EXPECT_EQ(effects.GetEffectsId(), 10);
}

TEST(CWeatherEffectsTest, SetEffectsName) {
    CWeatherEffects effects;
    effects.SetEffectsName("RainEffect");
    EXPECT_STREQ(effects.GetEffectsName(), "RainEffect");
}

TEST(CWeatherEffectsTest, SetEnabled) {
    CWeatherEffects effects;
    effects.SetEnabled(true);
    EXPECT_TRUE(effects.IsEnabled());
}

TEST(CWeatherEffectsTest, SetPlaying) {
    CWeatherEffects effects;
    effects.SetPlaying(true);
    EXPECT_TRUE(effects.IsPlaying());
}

TEST(CWeatherEffectsTest, SetIntensity) {
    CWeatherEffects effects;
    effects.SetIntensity(0.8f);
    EXPECT_FLOAT_EQ(effects.GetIntensity(), 0.8f);
}

TEST(CWeatherEffectsTest, SetDuration) {
    CWeatherEffects effects;
    effects.SetDuration(60.0f);
    EXPECT_FLOAT_EQ(effects.GetDuration(), 60.0f);
}

TEST(CWeatherEffectsTest, Update) {
    CWeatherEffects effects;
    effects.SetEnabled(true);
    effects.SetPlaying(true);
    effects.Update(1.0f);
    // Verify no crash
}

// Test TextureUtilities
TEST(TextureUtilitiesTest, CreateTexture) {
    uint32_t id = TextureUtilities::CreateTexture(64, 64, TextureUtilities::FORMAT_RGBA8);
    EXPECT_NE(id, 0u);
    EXPECT_EQ(TextureUtilities::GetTextureWidth(id), 64u);
    EXPECT_EQ(TextureUtilities::GetTextureHeight(id), 64u);
    TextureUtilities::UnloadTexture(id);
}

TEST(TextureUtilitiesTest, CreateTextureFromData) {
    uint8_t data[64 * 64 * 4];
    memset(data, 255, sizeof(data));
    uint32_t id = TextureUtilities::CreateTextureFromData(data, 64, 64, TextureUtilities::FORMAT_RGBA8);
    EXPECT_NE(id, 0u);
    TextureUtilities::UnloadTexture(id);
}

TEST(TextureUtilitiesTest, UnloadTexture) {
    uint32_t id = TextureUtilities::CreateTexture(32, 32, TextureUtilities::FORMAT_RGB8);
    TextureUtilities::UnloadTexture(id);
    EXPECT_EQ(TextureUtilities::GetTextureWidth(id), 0u);
}

TEST(TextureUtilitiesTest, CopyTexture) {
    uint32_t srcId = TextureUtilities::CreateTexture(64, 64, TextureUtilities::FORMAT_RGBA8);
    uint32_t dstId = TextureUtilities::CreateTexture(32, 32, TextureUtilities::FORMAT_RGBA8);
    EXPECT_TRUE(TextureUtilities::CopyTexture(srcId, dstId));
    EXPECT_EQ(TextureUtilities::GetTextureWidth(dstId), 64u);
    TextureUtilities::UnloadTexture(srcId);
    TextureUtilities::UnloadTexture(dstId);
}

TEST(TextureUtilitiesTest, GetTextureName) {
    uint32_t id = TextureUtilities::LoadTexture("test.dds");
    EXPECT_STREQ(TextureUtilities::GetTextureName(id), "test.dds");
    TextureUtilities::UnloadTexture(id);
}
