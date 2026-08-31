#include <gtest/gtest.h>
#include "Gx/Types.h"

TEST(GraphicTypesTest, BlitAlphaValues) {
    EXPECT_EQ(BlitAlpha_0, 0);
    EXPECT_EQ(BlitAlpha_1, 1);
    EXPECT_EQ(BlitAlpha_8, 2);
    EXPECT_EQ(BlitAlpha_Filler, 3);
    EXPECT_EQ(BlitAlphas_Last, 4);
}

TEST(GraphicTypesTest, GetBlitAlphaName) {
    EXPECT_STREQ(GetBlitAlphaName(BlitAlpha_0), "0");
    EXPECT_STREQ(GetBlitAlphaName(BlitAlpha_1), "1");
    EXPECT_STREQ(GetBlitAlphaName(BlitAlpha_8), "8");
    EXPECT_STREQ(GetBlitAlphaName(BlitAlpha_Filler), "Filler");
    EXPECT_STREQ(GetBlitAlphaName(static_cast<BlitAlpha>(10)), "Unknown");
}

TEST(GraphicTypesTest, BlitFormatValues) {
    EXPECT_EQ(BlitFormat_Unknown, 0);
    EXPECT_EQ(BlitFormat_Abgr8888, 1);
    EXPECT_EQ(BlitFormat_Argb8888, 2);
    EXPECT_EQ(BlitFormats_Last, 13);
}

TEST(GraphicTypesTest, GetBlitFormatName) {
    EXPECT_STREQ(GetBlitFormatName(BlitFormat_Unknown), "Unknown");
    EXPECT_STREQ(GetBlitFormatName(BlitFormat_Argb8888), "Argb8888");
    EXPECT_STREQ(GetBlitFormatName(BlitFormat_Dxt1), "Dxt1");
    EXPECT_STREQ(GetBlitFormatName(static_cast<BlitFormat>(100)), "Unknown");
}

TEST(GraphicTypesTest, GetBlitFormatBPP) {
    EXPECT_EQ(GetBlitFormatBPP(BlitFormat_Argb8888), 32u);
    EXPECT_EQ(GetBlitFormatBPP(BlitFormat_Argb4444), 16u);
    EXPECT_EQ(GetBlitFormatBPP(BlitFormat_Rgb565), 16u);
    EXPECT_EQ(GetBlitFormatBPP(BlitFormat_Dxt1), 4u);
    EXPECT_EQ(GetBlitFormatBPP(BlitFormat_Dxt3), 8u);
    EXPECT_EQ(GetBlitFormatBPP(BlitFormat_Dxt5), 8u);
    EXPECT_EQ(GetBlitFormatBPP(BlitFormat_Unknown), 0u);
}

TEST(GraphicTypesTest, EGxApiValues) {
    EXPECT_EQ(GxApi_OpenGl, 0);
    EXPECT_EQ(GxApi_D3d9, 1);
    EXPECT_EQ(GxApi_D3d11, 4);
    EXPECT_EQ(GxApis_Last, 6);
}

TEST(GraphicTypesTest, GetEGxApiName) {
    EXPECT_STREQ(GetEGxApiName(GxApi_OpenGl), "OpenGL");
    EXPECT_STREQ(GetEGxApiName(GxApi_D3d9), "D3D9");
    EXPECT_STREQ(GetEGxApiName(GxApi_D3d11), "D3D11");
    EXPECT_STREQ(GetEGxApiName(static_cast<EGxApi>(100)), "Unknown");
}

TEST(GraphicTypesTest, EGxBlendValues) {
    EXPECT_EQ(GxBlend_Opaque, 0);
    EXPECT_EQ(GxBlend_Alpha, 2);
    EXPECT_EQ(GxBlend_Add, 3);
    EXPECT_EQ(GxBlends_Last, 12);
}

TEST(GraphicTypesTest, GetEGxBlendName) {
    EXPECT_STREQ(GetEGxBlendName(GxBlend_Opaque), "Opaque");
    EXPECT_STREQ(GetEGxBlendName(GxBlend_Alpha), "Alpha");
    EXPECT_STREQ(GetEGxBlendName(GxBlend_Add), "Add");
    EXPECT_STREQ(GetEGxBlendName(static_cast<EGxBlend>(100)), "Unknown");
}

TEST(GraphicTypesTest, EGxTexFilterValues) {
    EXPECT_EQ(GxTex_Nearest, 0);
    EXPECT_EQ(GxTex_Linear, 1);
    EXPECT_EQ(GxTex_Anisotropic, 5);
    EXPECT_EQ(GxTexFilters_Last, 6);
}

TEST(GraphicTypesTest, GetEGxTexFilterName) {
    EXPECT_STREQ(GetEGxTexFilterName(GxTex_Nearest), "Nearest");
    EXPECT_STREQ(GetEGxTexFilterName(GxTex_Linear), "Linear");
    EXPECT_STREQ(GetEGxTexFilterName(GxTex_Anisotropic), "Anisotropic");
    EXPECT_STREQ(GetEGxTexFilterName(static_cast<EGxTexFilter>(100)), "Unknown");
}

TEST(GraphicTypesTest, EGxTexFormatValues) {
    EXPECT_EQ(GxTex_Unknown, 0);
    EXPECT_EQ(GxTex_Argb8888, 2);
    EXPECT_EQ(GxTex_Dxt5, 8);
    EXPECT_EQ(GxTexFormats_Last, 0xD);
}

TEST(GraphicTypesTest, GetEGxTexFormatName) {
    EXPECT_STREQ(GetEGxTexFormatName(GxTex_Unknown), "Unknown");
    EXPECT_STREQ(GetEGxTexFormatName(GxTex_Argb8888), "Argb8888");
    EXPECT_STREQ(GetEGxTexFormatName(GxTex_Dxt5), "Dxt5");
    EXPECT_STREQ(GetEGxTexFormatName(static_cast<EGxTexFormat>(100)), "Unknown");
}

TEST(GraphicTypesTest, EGxTexWrapModeValues) {
    EXPECT_EQ(GxTex_Clamp, 0);
    EXPECT_EQ(GxTex_Wrap, 1);
}

TEST(GraphicTypesTest, GetEGxTexWrapModeName) {
    EXPECT_STREQ(GetEGxTexWrapModeName(GxTex_Clamp), "Clamp");
    EXPECT_STREQ(GetEGxTexWrapModeName(GxTex_Wrap), "Wrap");
    EXPECT_STREQ(GetEGxTexWrapModeName(static_cast<EGxTexWrapMode>(10)), "Unknown");
}

TEST(GraphicTypesTest, EGxPrimValues) {
    EXPECT_EQ(GxPrim_Points, 0);
    EXPECT_EQ(GxPrim_Lines, 1);
    EXPECT_EQ(GxPrim_Triangles, 3);
    EXPECT_EQ(GxPrims_Last, 6);
}

TEST(GraphicTypesTest, GetEGxPrimName) {
    EXPECT_STREQ(GetEGxPrimName(GxPrim_Points), "Points");
    EXPECT_STREQ(GetEGxPrimName(GxPrim_Triangles), "Triangles");
    EXPECT_STREQ(GetEGxPrimName(GxPrim_TriangleFan), "TriangleFan");
    EXPECT_STREQ(GetEGxPrimName(static_cast<EGxPrim>(100)), "Unknown");
}
