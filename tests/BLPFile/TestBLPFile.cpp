#include <gtest/gtest.h>
#include "BLPFile/blp.h"
#include <cstring>

TEST(BLPFileTest, DefaultConstructor) {
    CBLPFile blp;
    EXPECT_EQ(blp.GetWidth(), 0u);
    EXPECT_EQ(blp.GetHeight(), 0u);
    EXPECT_EQ(blp.GetMipCount(), 0u);
}

TEST(BLPFileTest, LoadInvalidFile) {
    CBLPFile blp;
    EXPECT_EQ(blp.Open("nonexistent_file.blp"), 0);
}

TEST(BLPFileTest, OpenHeroArchmage) {
    CBLPFile blp;
    ASSERT_EQ(blp.Open("data/blp/HeroArchmage.blp"), 1);

    EXPECT_GT(blp.GetWidth(), 0u);
    EXPECT_GT(blp.GetHeight(), 0u);
    EXPECT_GT(blp.GetMipCount(), 0u);

    printf("HeroArchmage.blp: %ux%u, %u mips, %u alpha bits\n",
           blp.GetWidth(), blp.GetHeight(), blp.GetMipCount(), blp.GetAlphaBits());
}

TEST(BLPFileTest, DecodeMipDimensions) {
    CBLPFile blp;
    ASSERT_EQ(blp.Open("data/blp/HeroArchmage.blp"), 1);

    uint32_t outW = 0, outH = 0;
    ASSERT_EQ(blp.DecodeMip(0, nullptr, 0, &outW, &outH), 1);
    EXPECT_EQ(outW, blp.GetWidth());
    EXPECT_EQ(outH, blp.GetHeight());
}

TEST(BLPFileTest, DecodeMipData) {
    CBLPFile blp;
    ASSERT_EQ(blp.Open("data/blp/HeroArchmage.blp"), 1);

    uint32_t w = blp.GetWidth();
    uint32_t h = blp.GetHeight();
    std::vector<uint8_t> buf(w * h * 4);
    uint32_t outW = 0, outH = 0;

    ASSERT_EQ(blp.DecodeMip(0, buf.data(), buf.size(), &outW, &outH), 1);
    EXPECT_EQ(outW, w);
    EXPECT_EQ(outH, h);

    // 验证像素非全零
    bool hasContent = false;
    for (size_t i = 0; i < buf.size(); i += 4) {
        if (buf[i] != 0 || buf[i + 1] != 0 || buf[i + 2] != 0) {
            hasContent = true;
            break;
        }
    }
    EXPECT_TRUE(hasContent) << "Decoded image is all black";
}
