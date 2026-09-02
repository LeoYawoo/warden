#pragma once

#include <cstdint>

// Forward declarations
class CWar3Image;
class CTgaTexture;
class CBlpTexture;

// Reverse engineered from Warcraft III binary
// Image utility functions

namespace Images {
    // Image loading
    CWar3Image* LoadImage(const char* fileName);
    void UnloadImage(CWar3Image* image);

    // Texture loading
    CTgaTexture* LoadTgaTexture(const char* fileName);
    CBlpTexture* LoadBlpTexture(const char* fileName);
    void UnloadTexture(void* texture);

    // Image conversion
    bool ConvertToRGBA(const uint8_t* src, uint8_t* dst, uint32_t width, uint32_t height, uint32_t srcFormat);
    bool ConvertToRGB(const uint8_t* src, uint8_t* dst, uint32_t width, uint32_t height, uint32_t srcFormat);

    // Image scaling
    bool ScaleImage(const uint8_t* src, uint8_t* dst, uint32_t srcWidth, uint32_t srcHeight,
                    uint32_t dstWidth, uint32_t dstHeight, uint32_t format);

    // Format constants
    const uint32_t FORMAT_RGBA8 = 0;
    const uint32_t FORMAT_RGB8 = 1;
    const uint32_t FORMAT_ARGB8888 = 2;
    const uint32_t FORMAT_DXT1 = 3;
    const uint32_t FORMAT_DXT3 = 4;
    const uint32_t FORMAT_DXT5 = 5;
    const uint32_t FORMAT_PAL8 = 6;
}
