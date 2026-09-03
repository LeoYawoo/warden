#pragma once

#include <cstdint>
#include <string>

// Forward declarations
class CWar3Image;

// Reverse engineered from Warcraft III binary
// TextureUtilities provides texture utility functions

namespace TextureUtils {
    // Texture loading
    CWar3Image* LoadTexture(const char* fileName);
    void UnloadTexture(CWar3Image* image);

    // Texture information
    uint32_t GetTextureWidth(CWar3Image* image);
    uint32_t GetTextureHeight(CWar3Image* image);

    // Texture operations
    bool ConvertToRGBA(const uint8_t* src, uint8_t* dst, uint32_t width, uint32_t height, uint32_t srcFormat);
    bool ScaleTexture(const uint8_t* src, uint8_t* dst, uint32_t srcWidth, uint32_t srcHeight, uint32_t dstWidth, uint32_t dstHeight);

    // Format constants
    const uint32_t FORMAT_RGBA8 = 0;
    const uint32_t FORMAT_RGB8 = 1;
    const uint32_t FORMAT_DXT1 = 2;
    const uint32_t FORMAT_DXT3 = 3;
    const uint32_t FORMAT_DXT5 = 4;
}
