#pragma once

#include <cstdint>
#include <string>

// Reverse engineered from Warcraft III binary
// TextureUtilities provides texture utility functions

class TextureUtilities {
public:
    // Texture loading
    static uint32_t LoadTexture(const char* fileName);
    static void UnloadTexture(uint32_t textureId);

    // Texture information
    static uint32_t GetTextureWidth(uint32_t textureId);
    static uint32_t GetTextureHeight(uint32_t textureId);
    static const char* GetTextureName(uint32_t textureId);

    // Texture operations
    static bool SaveTexture(uint32_t textureId, const char* fileName);
    static bool CopyTexture(uint32_t srcId, uint32_t dstId);

    // Texture creation
    static uint32_t CreateTexture(uint32_t width, uint32_t height, uint32_t format);
    static uint32_t CreateTextureFromData(const void* data, uint32_t width, uint32_t height, uint32_t format);

    // Texture formats
    static const uint32_t FORMAT_RGBA8 = 0;
    static const uint32_t FORMAT_RGB8 = 1;
    static const uint32_t FORMAT_DXT1 = 2;
    static const uint32_t FORMAT_DXT3 = 3;
    static const uint32_t FORMAT_DXT5 = 4;
};
