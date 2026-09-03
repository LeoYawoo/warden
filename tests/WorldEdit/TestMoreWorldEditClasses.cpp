#include <gtest/gtest.h>
#include "WorldEdit/MapInfoFile.h"
#include "WorldEdit/TestGameFile.h"
#include "WorldEdit/TextureUtilities.h"

// Test MapInfoFile
TEST(MapInfoFileTest, DefaultConstructor) {
    MapInfoFile file;
    EXPECT_FALSE(file.IsValid());
    EXPECT_EQ(file.GetMapVersion(), 0);
    EXPECT_EQ(file.GetMapSize(), 0);
}

TEST(MapInfoFileTest, SetFileName) {
    MapInfoFile file;
    file.SetFileName("test.w3m");
    EXPECT_STREQ(file.GetFileName(), "test.w3m");
}

TEST(MapInfoFileTest, SetMapName) {
    MapInfoFile file;
    file.SetMapName("Test Map");
    EXPECT_STREQ(file.GetMapName(), "Test Map");
}

TEST(MapInfoFileTest, SetMapAuthor) {
    MapInfoFile file;
    file.SetMapAuthor("Author");
    EXPECT_STREQ(file.GetMapAuthor(), "Author");
}

TEST(MapInfoFileTest, SetMapDescription) {
    MapInfoFile file;
    file.SetMapDescription("A test map");
    EXPECT_STREQ(file.GetMapDescription(), "A test map");
}

TEST(MapInfoFileTest, SetMapVersion) {
    MapInfoFile file;
    file.SetMapVersion(3);
    EXPECT_EQ(file.GetMapVersion(), 3);
}

TEST(MapInfoFileTest, SetMapSize) {
    MapInfoFile file;
    file.SetMapSize(128);
    EXPECT_EQ(file.GetMapSize(), 128);
}

TEST(MapInfoFileTest, Load) {
    MapInfoFile file;
    EXPECT_TRUE(file.Load("test.w3m"));
    EXPECT_TRUE(file.IsValid());
}

// Test TestGameFile
TEST(TestGameFileTest, DefaultConstructor) {
    TestGameFile file;
    EXPECT_FALSE(file.IsLoaded());
    EXPECT_FALSE(file.IsValid());
}

TEST(TestGameFileTest, SetFileName) {
    TestGameFile file;
    file.SetFileName("test.w3g");
    EXPECT_STREQ(file.GetFileName(), "test.w3g");
}

TEST(TestGameFileTest, Load) {
    TestGameFile file;
    EXPECT_TRUE(file.Load("test.w3g"));
    EXPECT_TRUE(file.IsLoaded());
    EXPECT_TRUE(file.IsValid());
}

TEST(TestGameFileTest, Close) {
    TestGameFile file;
    file.Load("test.w3g");
    file.Close();
    EXPECT_FALSE(file.IsLoaded());
}

// Test TextureUtils
TEST(TextureUtilsTest, ConvertToRGBA) {
    uint8_t src[12] = {100, 150, 200, 100, 150, 200, 100, 150, 200};
    uint8_t dst[12];
    EXPECT_TRUE(TextureUtils::ConvertToRGBA(src, dst, 1, 3, TextureUtils::FORMAT_RGB8));
}

TEST(TextureUtilsTest, ScaleTexture) {
    uint8_t src[16] = {100, 150, 200, 255, 100, 150, 200, 255, 100, 150, 200, 255, 100, 150, 200, 255};
    uint8_t dst[16];
    EXPECT_TRUE(TextureUtils::ScaleTexture(src, dst, 2, 2, 2, 2));
}

TEST(TextureUtilsTest, InvalidInput) {
    EXPECT_FALSE(TextureUtils::ConvertToRGBA(nullptr, nullptr, 0, 0, 0));
    EXPECT_FALSE(TextureUtils::ScaleTexture(nullptr, nullptr, 0, 0, 0, 0));
}
