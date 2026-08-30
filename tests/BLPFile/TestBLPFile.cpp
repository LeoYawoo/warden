#include <gtest/gtest.h>
#include "BLPFile/blp.h"
#include <cstring>

TEST(BLPFileTest, DefaultConstructor) {
    CBLPFile blp;
    EXPECT_FALSE(blp.IsValid());
    EXPECT_EQ(blp.GetWidth(), 0u);
    EXPECT_EQ(blp.GetHeight(), 0u);
    EXPECT_EQ(blp.GetFormat(), BLP_FORMAT_JPEG);
    EXPECT_EQ(blp.GetNumMips(), 0u);
}

TEST(BLPFileTest, LoadInvalidMagic) {
    uint8_t data[164] = {0};
    // Set invalid magic number
    *reinterpret_cast<uint32_t*>(data) = 0x12345678;

    CBLPFile blp;
    EXPECT_FALSE(blp.LoadFromMemory(data, sizeof(data)));
    EXPECT_FALSE(blp.IsValid());
}

TEST(BLPFileTest, LoadValidHeader) {
    uint8_t data[256] = {0};

    // Set valid magic number
    *reinterpret_cast<uint32_t*>(data) = BLP_MAGIC;

    // Set version
    *reinterpret_cast<uint32_t*>(data + 4) = 1;

    // Set format to palette
    *reinterpret_cast<uint32_t*>(data + 8) = BLP_FORMAT_PALETTE;

    // Set width and height
    *reinterpret_cast<uint32_t*>(data + 16) = 64;
    *reinterpret_cast<uint32_t*>(data + 20) = 64;

    // Set mipmap count
    *reinterpret_cast<uint32_t*>(data + 152) = 1;

    // Set palette entries
    *reinterpret_cast<uint32_t*>(data + 156) = 256;

    // Set mipmap offset and size
    *reinterpret_cast<uint32_t*>(data + 24) = 164;  // offset
    *reinterpret_cast<uint32_t*>(data + 28) = 64;   // size

    CBLPFile blp;
    EXPECT_TRUE(blp.LoadFromMemory(data, sizeof(data)));
    EXPECT_TRUE(blp.IsValid());
    EXPECT_EQ(blp.GetWidth(), 64u);
    EXPECT_EQ(blp.GetHeight(), 64u);
    EXPECT_EQ(blp.GetFormat(), BLP_FORMAT_PALETTE);
    EXPECT_EQ(blp.GetNumMips(), 1u);
}

TEST(BLPFileTest, TooSmallData) {
    uint8_t data[100] = {0};
    CBLPFile blp;
    EXPECT_FALSE(blp.LoadFromMemory(data, sizeof(data)));
}

TEST(BLPFileTest, NullData) {
    CBLPFile blp;
    EXPECT_FALSE(blp.LoadFromMemory(nullptr, 100));
}

TEST(BLPFileTest, GetMipMapDataInvalid) {
    CBLPFile blp;
    EXPECT_EQ(blp.GetMipMapData(0), nullptr);
    EXPECT_EQ(blp.GetMipMapSize(0), 0u);
}

TEST(BLPFileTest, DecodeInvalid) {
    CBLPFile blp;
    std::vector<uint8_t> output;
    EXPECT_FALSE(blp.DecodeToRGBA(output));
}

TEST(BLPFileTest, DecodePaletteFormat) {
    uint8_t data[164 + 1024 + 4096] = {0};  // Header + palette + mipmap data

    // Set valid header
    *reinterpret_cast<uint32_t*>(data) = BLP_MAGIC;
    *reinterpret_cast<uint32_t*>(data + 4) = 1;
    *reinterpret_cast<uint32_t*>(data + 8) = BLP_FORMAT_PALETTE;
    *reinterpret_cast<uint32_t*>(data + 16) = 4;  // width
    *reinterpret_cast<uint32_t*>(data + 20) = 4;  // height
    *reinterpret_cast<uint32_t*>(data + 152) = 1;  // num mips
    *reinterpret_cast<uint32_t*>(data + 156) = 256;  // palette entries
    *reinterpret_cast<uint32_t*>(data + 24) = 164;  // mipmap offset
    *reinterpret_cast<uint32_t*>(data + 28) = 64;   // mipmap size (4x4 = 16 indices)

    // Set palette entries
    for (uint32_t i = 0; i < 256; ++i) {
        uint32_t *palette = reinterpret_cast<uint32_t*>(data + 164);
        palette[i] = (i << 24) | (i << 16) | (i << 8) | i;  // ARGB
    }

    CBLPFile blp;
    EXPECT_TRUE(blp.LoadFromMemory(data, sizeof(data)));
    EXPECT_TRUE(blp.IsValid());

    std::vector<uint8_t> output;
    EXPECT_TRUE(blp.DecodeToRGBA(output, 0));
    EXPECT_EQ(output.size(), 4 * 4 * 4u);  // 4x4 pixels * 4 bytes (RGBA)
}

TEST(BLPFileTest, DecodeDXT1Format) {
    uint8_t data[256] = {0};

    // Set valid header
    *reinterpret_cast<uint32_t*>(data) = BLP_MAGIC;
    *reinterpret_cast<uint32_t*>(data + 4) = 1;
    *reinterpret_cast<uint32_t*>(data + 8) = BLP_FORMAT_DXT1;
    *reinterpret_cast<uint32_t*>(data + 16) = 4;  // width
    *reinterpret_cast<uint32_t*>(data + 20) = 4;  // height
    *reinterpret_cast<uint32_t*>(data + 152) = 1;
    *reinterpret_cast<uint32_t*>(data + 24) = 164;
    *reinterpret_cast<uint32_t*>(data + 28) = 8;  // DXT1 block size

    CBLPFile blp;
    EXPECT_TRUE(blp.LoadFromMemory(data, sizeof(data)));
    EXPECT_TRUE(blp.IsValid());

    std::vector<uint8_t> output;
    EXPECT_TRUE(blp.DecodeToRGBA(output, 0));
    EXPECT_EQ(output.size(), 4 * 4 * 4u);
}

TEST(BLPFileTest, GetHeader) {
    uint8_t data[256] = {0};
    *reinterpret_cast<uint32_t*>(data) = BLP_MAGIC;
    *reinterpret_cast<uint32_t*>(data + 16) = 128;
    *reinterpret_cast<uint32_t*>(data + 20) = 256;

    CBLPFile blp;
    blp.LoadFromMemory(data, sizeof(data));

    const BLPHeader &header = blp.GetHeader();
    EXPECT_EQ(header.magic, BLP_MAGIC);
    EXPECT_EQ(header.width, 128u);
    EXPECT_EQ(header.height, 256u);
}

TEST(BLPFileTest, FormatEnumValues) {
    EXPECT_EQ(BLP_FORMAT_JPEG, 0);
    EXPECT_EQ(BLP_FORMAT_PALETTE, 1);
    EXPECT_EQ(BLP_FORMAT_DXT1, 2);
    EXPECT_EQ(BLP_FORMAT_DXT3, 3);
    EXPECT_EQ(BLP_FORMAT_DXT5, 4);
    EXPECT_EQ(BLP_FORMAT_UNCOMPRESSED, 5);
}

TEST(BLPFileTest, MagicNumber) {
    EXPECT_EQ(BLP_MAGIC, 0x31504C42u);
}

TEST(BLPFileTest, HeaderSize) {
    EXPECT_EQ(sizeof(BLPHeader), 164u);
}
