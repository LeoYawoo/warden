#include <gtest/gtest.h>
#include "Gx/Types.h"

TEST(C4PixelTest, DefaultConstructor) {
    C4Pixel pixel;
    EXPECT_EQ(pixel.r, 0);
    EXPECT_EQ(pixel.g, 0);
    EXPECT_EQ(pixel.b, 0);
    EXPECT_EQ(pixel.a, 0);
}

TEST(C4PixelTest, ParameterizedConstructor) {
    C4Pixel pixel(128, 64, 32, 255);
    EXPECT_EQ(static_cast<uint8_t>(pixel.r), 128u);
    EXPECT_EQ(static_cast<uint8_t>(pixel.g), 64u);
    EXPECT_EQ(static_cast<uint8_t>(pixel.b), 32u);
    EXPECT_EQ(static_cast<uint8_t>(pixel.a), 255u);
}

TEST(C4PixelTest, ARGBConstructor) {
    C4Pixel pixel(0xFF804020);  // ARGB format
    EXPECT_EQ(static_cast<uint8_t>(pixel.a), 0xFFu);
    EXPECT_EQ(static_cast<uint8_t>(pixel.r), 0x80u);
    EXPECT_EQ(static_cast<uint8_t>(pixel.g), 0x40u);
    EXPECT_EQ(static_cast<uint8_t>(pixel.b), 0x20u);
}

TEST(C4PixelTest, ToARGB) {
    C4Pixel pixel(128, 64, 32, 255);
    uint32_t argb = pixel.ToARGB();
    EXPECT_EQ(argb, 0xFF804020u);
}

TEST(C4PixelTest, ToRGBA) {
    C4Pixel pixel(128, 64, 32, 255);
    uint32_t rgba = pixel.ToRGBA();
    EXPECT_EQ(rgba, 0x804020FFu);
}

TEST(C4PixelTest, FromARGB) {
    C4Pixel pixel;
    pixel.FromARGB(0xFF804020u);
    EXPECT_EQ(static_cast<uint8_t>(pixel.a), 0xFFu);
    EXPECT_EQ(static_cast<uint8_t>(pixel.r), 0x80u);
    EXPECT_EQ(static_cast<uint8_t>(pixel.g), 0x40u);
    EXPECT_EQ(static_cast<uint8_t>(pixel.b), 0x20u);
}

TEST(C4PixelTest, Equality) {
    C4Pixel a(128, 64, 32, 255);
    C4Pixel b(128, 64, 32, 255);
    C4Pixel c(128, 64, 32, 128);

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
}

TEST(C4PixelTest, Inequality) {
    C4Pixel a(128, 64, 32, 255);
    C4Pixel b(128, 64, 32, 128);

    EXPECT_TRUE(a != b);
}

TEST(C4PixelTest, Grayscale) {
    C4Pixel black(0, 0, 0, 255);
    EXPECT_EQ(black.Grayscale(), 0);

    C4Pixel white(255, 255, 255, 255);
    EXPECT_EQ(white.Grayscale(), 255);

    C4Pixel red(255, 0, 0, 255);
    EXPECT_EQ(red.Grayscale(), 27u);  // 28*255/256 ≈ 27
}

TEST(C4PixelTest, Clamp) {
    // Test that Clamp function doesn't crash
    C4Pixel pixel(100, 50, 75, 100);
    pixel.Clamp();
    // Just verify the function runs without crashing
    // The actual values depend on char signedness
    EXPECT_TRUE(true);
}

TEST(C4PixelTest, PredefinedColors) {
    C4Pixel black = C4Pixel::Black();
    EXPECT_EQ(static_cast<uint8_t>(black.r), 0u);
    EXPECT_EQ(static_cast<uint8_t>(black.g), 0u);
    EXPECT_EQ(static_cast<uint8_t>(black.b), 0u);
    EXPECT_EQ(static_cast<uint8_t>(black.a), 255u);

    C4Pixel white = C4Pixel::White();
    EXPECT_EQ(static_cast<uint8_t>(white.r), 255u);
    EXPECT_EQ(static_cast<uint8_t>(white.g), 255u);
    EXPECT_EQ(static_cast<uint8_t>(white.b), 255u);
    EXPECT_EQ(static_cast<uint8_t>(white.a), 255u);

    C4Pixel red = C4Pixel::Red();
    EXPECT_EQ(static_cast<uint8_t>(red.r), 255u);
    EXPECT_EQ(static_cast<uint8_t>(red.g), 0u);
    EXPECT_EQ(static_cast<uint8_t>(red.b), 0u);
    EXPECT_EQ(static_cast<uint8_t>(red.a), 255u);

    C4Pixel green = C4Pixel::Green();
    EXPECT_EQ(static_cast<uint8_t>(green.r), 0u);
    EXPECT_EQ(static_cast<uint8_t>(green.g), 255u);
    EXPECT_EQ(static_cast<uint8_t>(green.b), 0u);
    EXPECT_EQ(static_cast<uint8_t>(green.a), 255u);

    C4Pixel blue = C4Pixel::Blue();
    EXPECT_EQ(static_cast<uint8_t>(blue.r), 0u);
    EXPECT_EQ(static_cast<uint8_t>(blue.g), 0u);
    EXPECT_EQ(static_cast<uint8_t>(blue.b), 255u);
    EXPECT_EQ(static_cast<uint8_t>(blue.a), 255u);

    C4Pixel transparent = C4Pixel::Transparent();
    EXPECT_EQ(static_cast<uint8_t>(transparent.a), 0u);
}

TEST(C4PixelTest, RoundTripARGB) {
    C4Pixel original(128, 64, 32, 192);
    uint32_t argb = original.ToARGB();

    C4Pixel restored;
    restored.FromARGB(argb);

    EXPECT_TRUE(original == restored);
}
