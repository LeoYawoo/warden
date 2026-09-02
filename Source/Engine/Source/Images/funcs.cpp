#include "funcs.h"
#include "CWar3Image.h"
#include "CTgaTexture.h"
#include "CBlpTexture.h"
#include "StormMac/Memory.h"
#include <cstring>

// Reverse engineered from Warcraft III binary

namespace Images {

CWar3Image* LoadImage(const char* fileName) {
    if (!fileName) return nullptr;

    CWar3Image* image = new CWar3Image();
    if (image->Load(fileName)) {
        return image;
    }

    delete image;
    return nullptr;
}

void UnloadImage(CWar3Image* image) {
    if (image) {
        delete image;
    }
}

CTgaTexture* LoadTgaTexture(const char* fileName) {
    if (!fileName) return nullptr;

    CTgaTexture* texture = new CTgaTexture();
    if (texture->Load(fileName)) {
        return texture;
    }

    delete texture;
    return nullptr;
}

CBlpTexture* LoadBlpTexture(const char* fileName) {
    if (!fileName) return nullptr;

    CBlpTexture* texture = new CBlpTexture();
    if (texture->Load(fileName)) {
        return texture;
    }

    delete texture;
    return nullptr;
}

void UnloadTexture(void* texture) {
    if (texture) {
        delete static_cast<CTgaTexture*>(texture);
    }
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

        case FORMAT_ARGB8888:
            for (uint32_t i = 0; i < pixelCount; i++) {
                dst[i * 4 + 0] = src[i * 4 + 1]; // R
                dst[i * 4 + 1] = src[i * 4 + 2]; // G
                dst[i * 4 + 2] = src[i * 4 + 3]; // B
                dst[i * 4 + 3] = src[i * 4 + 0]; // A
            }
            return true;

        default:
            return false;
    }
}

bool ConvertToRGB(const uint8_t* src, uint8_t* dst, uint32_t width, uint32_t height, uint32_t srcFormat) {
    if (!src || !dst) return false;

    uint32_t pixelCount = width * height;

    switch (srcFormat) {
        case FORMAT_RGBA8:
            for (uint32_t i = 0; i < pixelCount; i++) {
                dst[i * 3 + 0] = src[i * 4 + 0]; // R
                dst[i * 3 + 1] = src[i * 4 + 1]; // G
                dst[i * 3 + 2] = src[i * 4 + 2]; // B
            }
            return true;

        case FORMAT_ARGB8888:
            for (uint32_t i = 0; i < pixelCount; i++) {
                dst[i * 3 + 0] = src[i * 4 + 1]; // R
                dst[i * 3 + 1] = src[i * 4 + 2]; // G
                dst[i * 3 + 2] = src[i * 4 + 3]; // B
            }
            return true;

        default:
            return false;
    }
}

bool ScaleImage(const uint8_t* src, uint8_t* dst, uint32_t srcWidth, uint32_t srcHeight,
                uint32_t dstWidth, uint32_t dstHeight, uint32_t format) {
    if (!src || !dst || srcWidth == 0 || srcHeight == 0 || dstWidth == 0 || dstHeight == 0) {
        return false;
    }

    // Simple nearest-neighbor scaling
    float scaleX = static_cast<float>(srcWidth) / dstWidth;
    float scaleY = static_cast<float>(srcHeight) / dstHeight;

    uint32_t bytesPerPixel = (format == FORMAT_RGB8) ? 3 : 4;

    for (uint32_t y = 0; y < dstHeight; y++) {
        for (uint32_t x = 0; x < dstWidth; x++) {
            uint32_t srcX = static_cast<uint32_t>(x * scaleX);
            uint32_t srcY = static_cast<uint32_t>(y * scaleY);

            if (srcX >= srcWidth) srcX = srcWidth - 1;
            if (srcY >= srcHeight) srcY = srcHeight - 1;

            uint32_t srcOffset = (srcY * srcWidth + srcX) * bytesPerPixel;
            uint32_t dstOffset = (y * dstWidth + x) * bytesPerPixel;

            memcpy(&dst[dstOffset], &src[srcOffset], bytesPerPixel);
        }
    }

    return true;
}

} // namespace Images
