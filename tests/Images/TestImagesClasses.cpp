#include <gtest/gtest.h>
#include "Images/CWar3Image.h"
#include "Images/CTgaTexture.h"
#include "Images/CBlpTexture.h"
#include "Images/funcs.h"
#include "Images/tga.h"

// Test CWar3Image
TEST(CWar3ImageTest, DefaultConstructor) {
    CWar3Image image;
    EXPECT_EQ(image.GetImageId(), 0);
    EXPECT_FALSE(image.IsLoaded());
    EXPECT_EQ(image.GetWidth(), 0u);
    EXPECT_EQ(image.GetHeight(), 0u);
}

TEST(CWar3ImageTest, SetImageId) {
    CWar3Image image;
    image.SetImageId(42);
    EXPECT_EQ(image.GetImageId(), 42);
}

TEST(CWar3ImageTest, SetImageName) {
    CWar3Image image;
    image.SetImageName("test.tga");
    EXPECT_STREQ(image.GetImageName(), "test.tga");
}

TEST(CWar3ImageTest, SetSize) {
    CWar3Image image;
    image.SetSize(100, 200);
    EXPECT_EQ(image.GetWidth(), 100u);
    EXPECT_EQ(image.GetHeight(), 200u);
}

TEST(CWar3ImageTest, Load) {
    CWar3Image image;
    EXPECT_TRUE(image.Load("test.tga"));
    EXPECT_TRUE(image.IsLoaded());
}

TEST(CWar3ImageTest, Unload) {
    CWar3Image image;
    image.Load("test.tga");
    image.Unload();
    EXPECT_FALSE(image.IsLoaded());
}

// Test CTgaTexture
TEST(CTgaTextureTest, DefaultConstructor) {
    CTgaTexture texture;
    EXPECT_EQ(texture.GetTextureId(), 0);
    EXPECT_FALSE(texture.IsLoaded());
}

TEST(CTgaTextureTest, SetTextureId) {
    CTgaTexture texture;
    texture.SetTextureId(10);
    EXPECT_EQ(texture.GetTextureId(), 10);
}

TEST(CTgaTextureTest, SetTextureName) {
    CTgaTexture texture;
    texture.SetTextureName("texture.tga");
    EXPECT_STREQ(texture.GetTextureName(), "texture.tga");
}

TEST(CTgaTextureTest, SetSize) {
    CTgaTexture texture;
    texture.SetSize(256, 256);
    EXPECT_EQ(texture.GetWidth(), 256u);
    EXPECT_EQ(texture.GetHeight(), 256u);
}

TEST(CTgaTextureTest, SetFormat) {
    CTgaTexture texture;
    texture.SetFormat(2);
    EXPECT_EQ(texture.GetFormat(), 2u);
}

TEST(CTgaTextureTest, Load) {
    CTgaTexture texture;
    EXPECT_TRUE(texture.Load("texture.tga"));
    EXPECT_TRUE(texture.IsLoaded());
}

// Test CBlpTexture
TEST(CBlpTextureTest, DefaultConstructor) {
    CBlpTexture texture;
    EXPECT_EQ(texture.GetTextureId(), 0);
    EXPECT_FALSE(texture.IsLoaded());
}

TEST(CBlpTextureTest, SetTextureId) {
    CBlpTexture texture;
    texture.SetTextureId(5);
    EXPECT_EQ(texture.GetTextureId(), 5);
}

TEST(CBlpTextureTest, SetTextureName) {
    CBlpTexture texture;
    texture.SetTextureName("texture.blp");
    EXPECT_STREQ(texture.GetTextureName(), "texture.blp");
}

TEST(CBlpTextureTest, SetSize) {
    CBlpTexture texture;
    texture.SetSize(512, 512);
    EXPECT_EQ(texture.GetWidth(), 512u);
    EXPECT_EQ(texture.GetHeight(), 512u);
}

TEST(CBlpTextureTest, Load) {
    CBlpTexture texture;
    EXPECT_TRUE(texture.Load("texture.blp"));
    EXPECT_TRUE(texture.IsLoaded());
}

// Test Images namespace functions
TEST(ImagesTest, LoadImage) {
    CWar3Image* image = Images::LoadImage("test.tga");
    EXPECT_NE(image, nullptr);
    Images::UnloadImage(image);
}

TEST(ImagesTest, UnloadImage) {
    CWar3Image* image = Images::LoadImage("test.tga");
    Images::UnloadImage(image);
    // Verify no crash
}

TEST(ImagesTest, LoadTgaTexture) {
    CTgaTexture* texture = Images::LoadTgaTexture("texture.tga");
    EXPECT_NE(texture, nullptr);
}

TEST(ImagesTest, LoadBlpTexture) {
    CBlpTexture* texture = Images::LoadBlpTexture("texture.blp");
    EXPECT_NE(texture, nullptr);
}

// Test TGA namespace functions
TEST(TGATest, IsTGAFile) {
    EXPECT_TRUE(TGA::IsTGAFile("test.tga"));
    EXPECT_TRUE(TGA::IsTGAFile("test.TGA"));
    EXPECT_FALSE(TGA::IsTGAFile("test.png"));
    EXPECT_FALSE(TGA::IsTGAFile("test"));
}

TEST(TGATest, IsTGAData) {
    uint8_t header[18];
    memset(header, 0, sizeof(header));
    header[2] = TGA::TGA_UNCOMPRESSED_TRUECOLOR;
    EXPECT_TRUE(TGA::IsTGAData(header, sizeof(header)));

    header[2] = 99;
    EXPECT_FALSE(TGA::IsTGAData(header, sizeof(header)));
}

TEST(TGATest, CompressDecompressRLE) {
    uint8_t src[12];
    for (int i = 0; i < 4; i++) {
        src[i * 3] = 100;
        src[i * 3 + 1] = 150;
        src[i * 3 + 2] = 200;
    }

    uint8_t dst[12];
    uint32_t dstSize;

    EXPECT_TRUE(TGA::CompressRLE(src, dst, 12, &dstSize));
    EXPECT_GT(dstSize, 0u);

    uint8_t decompressed[12];
    EXPECT_TRUE(TGA::DecompressRLE(dst, decompressed, dstSize, 12));
}
