#include "TextureUtilities.h"

// Reverse engineered from Warcraft III binary

namespace TextureUtils {

uint32_t GetTextureWidth(void* image) {
    // Query texture width from image
    // In a real implementation, this would access the image structure
    // to get the width property
    if (image) {
        // Access image width from the image structure
        // The exact implementation depends on the image format
        return 0; // Placeholder
    }
    return 0;
}

uint32_t GetTextureHeight(void* image) {
    // Query texture height from image
    // In a real implementation, this would access the image structure
    // to get the height property
    if (image) {
        // Access image height from the image structure
        // The exact implementation depends on the image format
        return 0; // Placeholder
    }
    return 0;
}

bool ConvertToRGBA(const uint8_t* src, uint8_t* dst, uint32_t width, uint32_t height, uint32_t srcFormat) {
    if (!src || !dst) return false;

    uint32_t pixelCount = width * height;

    switch (srcFormat) {
        case FORMAT_RGB8:
            for (uint32_t i = 0; i < pixelCount; i++) {
                dst[i * 4 + 0] = src[i * 3 + 0]; // R
                dst[i * 4 + 1] = src[i * 3 + 1]; // G
                dst[i * 4 + 2] = src[i * 3 + 2]; // B
                dst[i * 4 + 3] = 255;             // A
            }
            return true;

        default:
            return false;
    }
}

bool ScaleTexture(const uint8_t* src, uint8_t* dst, uint32_t srcWidth, uint32_t srcHeight, uint32_t dstWidth, uint32_t dstHeight) {
    if (!src || !dst || srcWidth == 0 || srcHeight == 0 || dstWidth == 0 || dstHeight == 0) {
        return false;
    }

    float scaleX = static_cast<float>(srcWidth) / dstWidth;
    float scaleY = static_cast<float>(srcHeight) / dstHeight;

    for (uint32_t y = 0; y < dstHeight; y++) {
        for (uint32_t x = 0; x < dstWidth; x++) {
            uint32_t srcX = static_cast<uint32_t>(x * scaleX);
            uint32_t srcY = static_cast<uint32_t>(y * scaleY);

            if (srcX >= srcWidth) srcX = srcWidth - 1;
            if (srcY >= srcHeight) srcY = srcHeight - 1;

            uint32_t srcOffset = (srcY * srcWidth + srcX) * 4;
            uint32_t dstOffset = (y * dstWidth + x) * 4;

            dst[dstOffset + 0] = src[srcOffset + 0];
            dst[dstOffset + 1] = src[srcOffset + 1];
            dst[dstOffset + 2] = src[srcOffset + 2];
            dst[dstOffset + 3] = src[srcOffset + 3];
        }
    }

    return true;
}

} // namespace TextureUtils
