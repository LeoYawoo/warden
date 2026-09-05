#include <gtest/gtest.h>
#include "BLPFile/blp.h"
#include <fstream>
#include <vector>
#include <cstring>

// TGA file writer helper
static bool WriteTGA(const char *path, uint32_t width, uint32_t height, const uint8_t *bgra) {
    std::ofstream file(path, std::ios::binary);
    if (!file.is_open()) return false;

    uint8_t header[18] = {};
    header[2] = 2;
    header[12] = width & 0xFF;
    header[13] = (width >> 8) & 0xFF;
    header[14] = height & 0xFF;
    header[15] = (height >> 8) & 0xFF;
    header[16] = 32;
    header[17] = 0x28;

    file.write(reinterpret_cast<const char *>(header), 18);
    file.write(reinterpret_cast<const char *>(bgra), width * height * 4);
    return file.good();
}

// ============================================================
// ST: BLP 解码管线集成验证
// ============================================================

// ST-BLP-001: HeroArchmage.blp 基本属性验证
TEST(BLPDecodeIntegration, HeroArchmageProperties) {
    const char *blpPath = "data/blp/HeroArchmage.blp";

    CBLPLoader blp;
    ASSERT_EQ(blp.Open(blpPath), 1) << "Failed to load " << blpPath;

    uint32_t width = blp.GetWidth();
    uint32_t height = blp.GetHeight();
    EXPECT_GT(width, 0u);
    EXPECT_GT(height, 0u);

    uint32_t numMips = blp.GetMipCount();
    EXPECT_GT(numMips, 0u) << "No mipmaps found";

    uint32_t alphaBits = blp.GetAlphaBits();
    EXPECT_GE(alphaBits, 0u);

    // 打印信息供调试
    printf("HeroArchmage.blp: %ux%u, %u mipmaps, %u alpha bits\n",
           width, height, numMips, alphaBits);
}

// ST-BLP-002: HeroArchmage.blp mipmap 解码验证
TEST(BLPDecodeIntegration, HeroArchmageMipDecode) {
    const char *blpPath = "data/blp/HeroArchmage.blp";

    CBLPLoader blp;
    ASSERT_EQ(blp.Open(blpPath), 1);

    uint32_t width = blp.GetWidth();
    uint32_t height = blp.GetHeight();
    uint32_t numMips = blp.GetMipCount();

    for (uint32_t level = 0; level < numMips; ++level) {
        uint32_t outW = 0, outH = 0;

        // 先查询尺寸
        int32_t result = blp.DecodeMip(level, nullptr, 0, &outW, &outH);

        if (outW > 1 && outH > 1) {
            std::vector<uint8_t> buf(outW * outH * 4);
            result = blp.DecodeMip(level, buf.data(), buf.size(), &outW, &outH);
            EXPECT_EQ(result, 1) << "Failed to decode mip level " << level;

            // 验证像素非全零
            bool hasContent = false;
            for (size_t i = 0; i < buf.size(); i += 4) {
                if (buf[i] != 0 || buf[i + 1] != 0 || buf[i + 2] != 0) {
                    hasContent = true;
                    break;
                }
            }
            EXPECT_TRUE(hasContent) << "Mip level " << level << " is all black";
        }
    }
}

// ST-BLP-003: HeroArchmage.blp → TGA 文件输出验证
TEST(BLPDecodeIntegration, HeroArchmageToTGA) {
    const char *blpPath = "data/blp/HeroArchmage.blp";
    const char *tgaPath = "data/blp/HeroArchmage_decoded.tga";

    CBLPLoader blp;
    ASSERT_EQ(blp.Open(blpPath), 1);

    uint32_t width = blp.GetWidth();
    uint32_t height = blp.GetHeight();

    uint32_t outW = 0, outH = 0;
    std::vector<uint8_t> buf(width * height * 4);
    ASSERT_EQ(blp.DecodeMip(0, buf.data(), buf.size(), &outW, &outH), 1);

    // 写入 TGA（BLP 输出是 BGRA，TGA 也是 BGRA，直接写入）
    ASSERT_TRUE(WriteTGA(tgaPath, outW, outH, buf.data()));

    // 验证文件存在且大小正确
    std::ifstream file(tgaPath, std::ios::binary | std::ios::ate);
    ASSERT_TRUE(file.is_open());
    size_t fileSize = static_cast<size_t>(file.tellg());
    EXPECT_EQ(fileSize, 18u + outW * outH * 4u);

    printf("TGA output: %s (%ux%u, %zu bytes)\n", tgaPath, outW, outH, fileSize);
}

// ST-BLP-004: 多次解码结果一致（幂等性）
TEST(BLPDecodeIntegration, HeroArchmageIdempotent) {
    const char *blpPath = "data/blp/HeroArchmage.blp";

    CBLPLoader blp;
    ASSERT_EQ(blp.Open(blpPath), 1);

    uint32_t width = blp.GetWidth();
    uint32_t height = blp.GetHeight();

    std::vector<uint8_t> buf1(width * height * 4);
    std::vector<uint8_t> buf2(width * height * 4);
    uint32_t w1, h1, w2, h2;

    blp.DecodeMip(0, buf1.data(), buf1.size(), &w1, &h1);
    blp.DecodeMip(0, buf2.data(), buf2.size(), &w2, &h2);

    EXPECT_EQ(w1, w2);
    EXPECT_EQ(h1, h2);
    EXPECT_EQ(buf1, buf2) << "Decode is not idempotent";
}

// ST-BLP-005: ffmpeg 转换参考输出对比
// 注意: ffmpeg 不支持 BLP 格式，此测试验证 TGA 输出可被 ffmpeg 读取
TEST(BLPDecodeIntegration, TGAReadableByFFmpeg) {
    const char *blpPath = "data/blp/HeroArchmage.blp";
    const char *tgaPath = "data/blp/HeroArchmage_test.tga";
    const char *pngPath = "data/blp/HeroArchmage_test.png";
    const char *ffmpegPath = "data/tools/ffmpeg/ffmpeg.exe";

    CBLPLoader blp;
    ASSERT_EQ(blp.Open(blpPath), 1);

    uint32_t width = blp.GetWidth();
    uint32_t height = blp.GetHeight();

    uint32_t outW = 0, outH = 0;
    std::vector<uint8_t> buf(width * height * 4);
    ASSERT_EQ(blp.DecodeMip(0, buf.data(), buf.size(), &outW, &outH), 1);

    // 写 TGA
    ASSERT_TRUE(WriteTGA(tgaPath, outW, outH, buf.data()));

    // 用 ffmpeg 转换 TGA → PNG 验证 TGA 格式正确
    // 从项目根目录执行
    std::string cmd = std::string("cd D:\\workcode\\game\\warden && \"") + ffmpegPath + "\" -i \"" + tgaPath + "\" -y \"" + pngPath + "\" 2>nul";
    int ret = system(cmd.c_str());
    EXPECT_EQ(ret, 0) << "ffmpeg failed to convert TGA to PNG";

    // 验证 PNG 文件存在
    std::ifstream pngFile(pngPath, std::ios::binary | std::ios::ate);
    EXPECT_TRUE(pngFile.is_open()) << "PNG output file not created";
    EXPECT_GT(static_cast<size_t>(pngFile.tellg()), 0u);
}
