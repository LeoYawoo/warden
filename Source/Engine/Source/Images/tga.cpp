#include "tga.h"
#include "CWar3Image.h"
#include "StormMac/Memory.h"
#include <cstring>
#include <fstream>

// Reverse engineered from Warcraft III binary

namespace TGA {

bool LoadTGA(const char* fileName, CWar3Image* image) {
    if (!fileName || !image) return false;

    std::ifstream file(fileName, std::ios::binary);
    if (!file.is_open()) return false;

    TGAHeader header;
    file.read(reinterpret_cast<char*>(&header), sizeof(header));

    if (header.imageType != TGA_UNCOMPRESSED_TRUECOLOR && header.imageType != TGA_RLE_TRUECOLOR) {
        file.close();
        return false;
    }

    image->SetSize(header.width, header.height);

    uint32_t pixelCount = header.width * header.height;
    uint32_t bytesPerPixel = header.bitsPerPixel / 8;
    uint32_t dataSize = pixelCount * bytesPerPixel;

    uint8_t* data = static_cast<uint8_t*>(SMemAlloc(dataSize, __FILE__, __LINE__, 0));
    if (!data) {
        file.close();
        return false;
    }

    if (header.imageType == TGA_RLE_TRUECOLOR) {
        // RLE compressed
        uint32_t srcPos = 0;
        uint32_t dstPos = 0;

        while (dstPos < dataSize) {
            uint8_t chunkHeader;
            file.read(reinterpret_cast<char*>(&chunkHeader), 1);

            if (chunkHeader < 128) {
                // Raw chunk
                uint8_t count = chunkHeader + 1;
                file.read(reinterpret_cast<char*>(&data[dstPos]), count * bytesPerPixel);
                dstPos += count * bytesPerPixel;
            } else {
                // RLE chunk
                uint8_t count = chunkHeader - 127;
                uint8_t pixel[4];
                file.read(reinterpret_cast<char*>(pixel), bytesPerPixel);

                for (uint8_t i = 0; i < count; i++) {
                    memcpy(&data[dstPos], pixel, bytesPerPixel);
                    dstPos += bytesPerPixel;
                }
            }
        }
    } else {
        // Uncompressed
        file.read(reinterpret_cast<char*>(data), dataSize);
    }

    file.close();

    // Convert BGR to RGB if needed
    if (bytesPerPixel == 3) {
        for (uint32_t i = 0; i < pixelCount; i++) {
            uint8_t temp = data[i * 3];
            data[i * 3] = data[i * 3 + 2];
            data[i * 3 + 2] = temp;
        }
    } else if (bytesPerPixel == 4) {
        for (uint32_t i = 0; i < pixelCount; i++) {
            uint8_t temp = data[i * 4];
            data[i * 4] = data[i * 4 + 2];
            data[i * 4 + 2] = temp;
        }
    }

    // Store data in image (simplified)
    // In real implementation, would need to store data pointer in image

    return true;
}

bool SaveTGA(const char* fileName, const uint8_t* data, uint32_t width, uint32_t height, uint32_t bitsPerPixel) {
    if (!fileName || !data) return false;

    std::ofstream file(fileName, std::ios::binary);
    if (!file.is_open()) return false;

    TGAHeader header;
    memset(&header, 0, sizeof(header));
    header.imageType = TGA_UNCOMPRESSED_TRUECOLOR;
    header.width = width;
    header.height = height;
    header.bitsPerPixel = bitsPerPixel;
    header.imageDescriptor = 0x20; // Top-left origin

    file.write(reinterpret_cast<const char*>(&header), sizeof(header));
    file.write(reinterpret_cast<const char*>(data), width * height * (bitsPerPixel / 8));

    file.close();
    return true;
}

bool IsTGAFile(const char* fileName) {
    if (!fileName) return false;

    size_t len = strlen(fileName);
    if (len < 4) return false;

    return strcmp(&fileName[len - 4], ".tga") == 0 || strcmp(&fileName[len - 4], ".TGA") == 0;
}

bool IsTGAData(const uint8_t* data, uint32_t size) {
    if (!data || size < 18) return false;

    // Check for valid TGA header
    TGAHeader header;
    memcpy(&header, data, sizeof(header));

    return header.imageType <= TGA_RLE_GRAYSCALE;
}

bool CompressRLE(const uint8_t* src, uint8_t* dst, uint32_t srcSize, uint32_t* dstSize) {
    if (!src || !dst || !dstSize) return false;

    uint32_t srcPos = 0;
    uint32_t dstPos = 0;
    uint32_t bytesPerPixel = 3; // Assume RGB

    while (srcPos < srcSize) {
        uint8_t runStart = srcPos;
        uint8_t runLength = 1;

        // Count similar pixels
        while (srcPos + runLength * bytesPerPixel < srcSize && runLength < 128) {
            if (memcmp(&src[(srcPos + runLength) * bytesPerPixel],
                       &src[srcPos * bytesPerPixel], bytesPerPixel) != 0) {
                break;
            }
            runLength++;
        }

        if (runLength >= 3) {
            // RLE chunk
            dst[dstPos++] = 128 + (runLength - 1);
            memcpy(&dst[dstPos], &src[srcPos * bytesPerPixel], bytesPerPixel);
            dstPos += bytesPerPixel;
            srcPos += runLength * bytesPerPixel;
        } else {
            // Raw chunk
            dst[dstPos++] = 0;
            for (uint8_t i = 0; i < runLength; i++) {
                memcpy(&dst[dstPos], &src[(srcPos + i) * bytesPerPixel], bytesPerPixel);
                dstPos += bytesPerPixel;
            }
            srcPos += runLength * bytesPerPixel;
        }
    }

    *dstSize = dstPos;
    return true;
}

bool DecompressRLE(const uint8_t* src, uint8_t* dst, uint32_t srcSize, uint32_t dstSize) {
    if (!src || !dst) return false;

    uint32_t srcPos = 0;
    uint32_t dstPos = 0;
    uint32_t bytesPerPixel = 3; // Assume RGB

    while (srcPos < srcSize && dstPos < dstSize) {
        uint8_t chunkHeader = src[srcPos++];

        if (chunkHeader < 128) {
            // Raw chunk
            uint8_t count = chunkHeader + 1;
            memcpy(&dst[dstPos], &src[srcPos], count * bytesPerPixel);
            dstPos += count * bytesPerPixel;
            srcPos += count * bytesPerPixel;
        } else {
            // RLE chunk
            uint8_t count = chunkHeader - 127;
            for (uint8_t i = 0; i < count; i++) {
                memcpy(&dst[dstPos], &src[srcPos], bytesPerPixel);
                dstPos += bytesPerPixel;
            }
            srcPos += bytesPerPixel;
        }
    }

    return true;
}

} // namespace TGA
