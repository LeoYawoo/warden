#include <gtest/gtest.h>
#include "Gxu/IGxuFont.h"
#include "Gxu/GxuFont.h"
#include "Gxu/GxuFontUtil.h"
#include "Gxu/GxuLight.h"
#include "Gxu/IGxuFontGlyph.h"

// Test GxuFont
TEST(GxuFontTest, DefaultConstructor) {
    GxuFont font;
    EXPECT_FALSE(font.IsLoaded());
    EXPECT_FLOAT_EQ(font.GetScale(), 1.0f);
}

TEST(GxuFontTest, Load) {
    GxuFont font;
    EXPECT_TRUE(font.Load("Arial.ttf"));
    EXPECT_TRUE(font.IsLoaded());
}

TEST(GxuFontTest, Unload) {
    GxuFont font;
    font.Load("Arial.ttf");
    font.Unload();
    EXPECT_FALSE(font.IsLoaded());
}

TEST(GxuFontTest, SetGetScale) {
    GxuFont font;
    font.SetScale(2.0f);
    EXPECT_FLOAT_EQ(font.GetScale(), 2.0f);
}

TEST(GxuFontTest, SetGetFontName) {
    GxuFont font;
    font.SetFontName("Times New Roman");
    EXPECT_STREQ(font.GetFontName(), "Times New Roman");
}

// Test GxuFontUtil
TEST(GxuFontUtilTest, CreateFont) {
    IGxuFont* font = GxuFontUtil::CreateFont("Arial.ttf");
    EXPECT_NE(font, nullptr);
    GxuFontUtil::DestroyFont(font);
}

TEST(GxuFontUtilTest, DestroyFont) {
    IGxuFont* font = GxuFontUtil::CreateFont("Arial.ttf");
    GxuFontUtil::DestroyFont(font);
    // Verify no crash
}

TEST(GxuFontUtilTest, GetStringWidth) {
    IGxuFont* font = GxuFontUtil::CreateFont("Arial.ttf");
    float width = GxuFontUtil::GetStringWidth(font, "Hello");
    EXPECT_GE(width, 0.0f);
    GxuFontUtil::DestroyFont(font);
}

TEST(GxuFontUtilTest, GetStringHeight) {
    IGxuFont* font = GxuFontUtil::CreateFont("Arial.ttf");
    float height = GxuFontUtil::GetStringHeight(font, "Hello");
    EXPECT_GE(height, 0.0f);
    GxuFontUtil::DestroyFont(font);
}

// Test GxuLight
TEST(GxuLightTest, DefaultConstructor) {
    GxuLight light;
    EXPECT_EQ(light.GetLightId(), 0);
    EXPECT_TRUE(light.IsEnabled());
    EXPECT_FLOAT_EQ(light.GetIntensity(), 1.0f);
}

TEST(GxuLightTest, SetLightId) {
    GxuLight light;
    light.SetLightId(42);
    EXPECT_EQ(light.GetLightId(), 42);
}

TEST(GxuLightTest, SetLightType) {
    GxuLight light;
    light.SetLightType(1);
    EXPECT_EQ(light.GetLightType(), 1);
}

TEST(GxuLightTest, SetColor) {
    GxuLight light;
    light.SetColor(0.5f, 0.7f, 0.9f);
    EXPECT_FLOAT_EQ(light.GetRed(), 0.5f);
    EXPECT_FLOAT_EQ(light.GetGreen(), 0.7f);
    EXPECT_FLOAT_EQ(light.GetBlue(), 0.9f);
}

TEST(GxuLightTest, SetIntensity) {
    GxuLight light;
    light.SetIntensity(2.0f);
    EXPECT_FLOAT_EQ(light.GetIntensity(), 2.0f);
}

TEST(GxuLightTest, SetRange) {
    GxuLight light;
    light.SetRange(500.0f);
    EXPECT_FLOAT_EQ(light.GetRange(), 500.0f);
}

TEST(GxuLightTest, SetPosition) {
    GxuLight light;
    light.SetPosition(10.0f, 20.0f, 30.0f);
    EXPECT_FLOAT_EQ(light.GetX(), 10.0f);
    EXPECT_FLOAT_EQ(light.GetY(), 20.0f);
    EXPECT_FLOAT_EQ(light.GetZ(), 30.0f);
}

TEST(GxuLightTest, SetDirection) {
    GxuLight light;
    light.SetDirection(0.0f, 1.0f, 0.0f);
    EXPECT_FLOAT_EQ(light.GetDirX(), 0.0f);
    EXPECT_FLOAT_EQ(light.GetDirY(), 1.0f);
    EXPECT_FLOAT_EQ(light.GetDirZ(), 0.0f);
}

TEST(GxuLightTest, SetEnabled) {
    GxuLight light;
    light.SetEnabled(false);
    EXPECT_FALSE(light.IsEnabled());
}
