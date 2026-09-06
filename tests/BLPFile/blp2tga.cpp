// blp2tga - BLP to TGA/PNG converter
// Usage: blp2tga <input.blp> <output.tga> [--dump-png]

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../../external/stb_image_write_new.h"

#include "BLPFile/blp.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <vector>
#include <string>

// ============================================================
// TGA writer
// ============================================================
static bool WriteTGA(const char *path, uint32_t width, uint32_t height, const uint8_t *rgba) {
    std::ofstream file(path, std::ios::binary);
    if (!file.is_open()) return false;

    uint8_t header[18] = {};
    header[2] = 2;       // Uncompressed true-color
    header[12] = width & 0xFF;
    header[13] = (width >> 8) & 0xFF;
    header[14] = height & 0xFF;
    header[15] = (height >> 8) & 0xFF;
    header[16] = 32;     // 32 bits per pixel
    header[17] = 0x28;   // top-to-bottom, 8-bit alpha

    file.write(reinterpret_cast<const char *>(header), 18);

    // TGA uses BGRA byte order, swap R and B from RGBA
    std::vector<uint8_t> bgra(width * height * 4);
    for (uint32_t i = 0; i < width * height; ++i) {
        bgra[i * 4 + 0] = rgba[i * 4 + 2]; // B
        bgra[i * 4 + 1] = rgba[i * 4 + 1]; // G
        bgra[i * 4 + 2] = rgba[i * 4 + 0]; // R
        bgra[i * 4 + 3] = rgba[i * 4 + 3]; // A
    }

    file.write(reinterpret_cast<const char *>(bgra.data()), bgra.size());
    return file.good();
}

// ============================================================
// PNG writer (using stb_image_write)
// ============================================================
static bool WritePNG(const char *path, uint32_t width, uint32_t height, const uint8_t *rgba) {
    // stb_image_write expects stride (bytes per row)
    int stride = width * 4;
    int ret = stbi_write_png(path, width, height, 4, rgba, stride);
    return ret != 0;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <input.blp> <output.tga> [--dump-png]\n", argv[0]);
        return 1;
    }

    const char *blpPath = argv[1];
    const char *tgaPath = argv[2];
    bool dumpPng = false;

    for (int i = 3; i < argc; i++) {
        if (strcmp(argv[i], "--dump-png") == 0) {
            dumpPng = true;
        }
    }

    CBLPFile blp;
    if (!blp.Open(blpPath)) {
        fprintf(stderr, "Failed to open %s\n", blpPath);
        return 1;
    }

    printf("BLP: %ux%u, %u mipmaps, %u alpha bits\n",
           blp.GetWidth(), blp.GetHeight(), blp.GetMipCount(), blp.GetAlphaBits());

    uint32_t outW = 0, outH = 0;
    std::vector<uint8_t> buf(blp.GetWidth() * blp.GetHeight() * 4);

    if (!blp.DecodeMip(0, buf.data(), buf.size(), &outW, &outH)) {
        fprintf(stderr, "Failed to decode mip 0\n");
        return 1;
    }

    if (!WriteTGA(tgaPath, outW, outH, buf.data())) {
        fprintf(stderr, "Failed to write %s\n", tgaPath);
        return 1;
    }
    printf("TGA: %s (%ux%u)\n", tgaPath, outW, outH);

    if (dumpPng) {
        std::string pngPath = std::string(tgaPath);
        size_t dotPos = pngPath.rfind('.');
        if (dotPos != std::string::npos) {
            pngPath = pngPath.substr(0, dotPos) + "_mip0.png";
        } else {
            pngPath += "_mip0.png";
        }

        if (WritePNG(pngPath.c_str(), outW, outH, buf.data())) {
            printf("PNG: %s (%ux%u)\n", pngPath.c_str(), outW, outH);
        } else {
            fprintf(stderr, "Failed to write %s\n", pngPath.c_str());
        }
    }

    return 0;
}
