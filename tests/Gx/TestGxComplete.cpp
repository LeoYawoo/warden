#include <gtest/gtest.h>
#include "Gx/Types.h"
#include "Gx/CGxBatch.h"
#include "Gx/CGxCaps.h"

// Test Types.h - Enums and inline functions (not already tested in TestGraphicTypes.cpp)
TEST(TypesTest, GetEGxTexWrapModeName) {
    EXPECT_STREQ(GetEGxTexWrapModeName(GxTex_Clamp), "Clamp");
    EXPECT_STREQ(GetEGxTexWrapModeName(GxTex_Wrap), "Wrap");
    EXPECT_STREQ(GetEGxTexWrapModeName(static_cast<EGxTexWrapMode>(99)), "Unknown");
}

// Test CGxBatch
TEST(CGxBatchTest, DefaultConstructor) {
    CGxBatch batch;
    batch.m_start = 0;
    batch.m_count = 0;
    EXPECT_EQ(batch.m_start, 0u);
    EXPECT_EQ(batch.m_count, 0u);
}

TEST(CGxBatchTest, SetFields) {
    CGxBatch batch;
    batch.m_primType = GxPrim_Triangles;
    batch.m_start = 100;
    batch.m_count = 50;
    batch.m_minIndex = 0;
    batch.m_maxIndex = 99;
    EXPECT_EQ(batch.m_primType, GxPrim_Triangles);
    EXPECT_EQ(batch.m_start, 100u);
    EXPECT_EQ(batch.m_count, 50u);
}

// Test CGxCaps
TEST(CGxCapsTest, DefaultValues) {
    CGxCaps caps;
    EXPECT_EQ(caps.m_numTmus, 0);
    EXPECT_EQ(caps.m_colorFormat, GxCF_argb);
    EXPECT_EQ(caps.m_maxIndex, 0u);
    EXPECT_EQ(caps.m_generateMipMaps, 0);
}

TEST(CGxCapsTest, SetValues) {
    CGxCaps caps;
    caps.m_numTmus = 4;
    caps.m_colorFormat = GxCF_rgba;
    caps.m_maxIndex = 65535;
    caps.m_generateMipMaps = 1;
    EXPECT_EQ(caps.m_numTmus, 4);
    EXPECT_EQ(caps.m_colorFormat, GxCF_rgba);
    EXPECT_EQ(caps.m_maxIndex, 65535u);
    EXPECT_EQ(caps.m_generateMipMaps, 1);
}
