#pragma once

#include <cstdint>

// Forward declarations
class CWar3Image;

// Reverse engineered from Warcraft III binary
// TGA file format utilities

namespace TGA {
    // TGA header structure
    struct TGAHeader {
        uint8_t idLength;
        uint8_t colorMapType;
        uint8_t imageType;
        uint8_t colorMapSpec[5];
        uint16_t xOrigin;
        uint16_t yOrigin;
        uint16_t width;
        uint16_t height;
        uint8_t bitsPerPixel;
        uint8_t imageDescriptor;
    };

    // TGA file operations
    bool LoadTGA(const char* fileName, CWar3Image* image);
    bool SaveTGA(const char* fileName, const uint8_t* data, uint32_t width, uint32_t height, uint32_t bitsPerPixel);

    // TGA format detection
    bool IsTGAFile(const char* fileName);
    bool IsTGAData(const uint8_t* data, uint32_t size);

    // TGA compression
    bool CompressRLE(const uint8_t* src, uint8_t* dst, uint32_t srcSize, uint32_t* dstSize);
    bool DecompressRLE(const uint8_t* src, uint8_t* dst, uint32_t srcSize, uint32_t dstSize);

    // TGA constants
    const uint8_t TGA_NO_IMAGE = 0;
    const uint8_t TGA_UNCOMPRESSED_COLORMAP = 1;
    const uint8_t TGA_UNCOMPRESSED_TRUECOLOR = 2;
    const uint8_t TGA_UNCOMPRESSED_GRAYSCALE = 3;
    const uint8_t TGA_RLE_COLORMAP = 9;
    const uint8_t TGA_RLE_TRUECOLOR = 10;
    const uint8_t TGA_RLE_GRAYSCALE = 11;
}
