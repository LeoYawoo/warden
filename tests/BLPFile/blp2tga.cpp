// blp2tga - BLP to TGA converter
// Usage: blp2tga <input.blp> <output.tga>

#include "BLPFile/blp.h"
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <vector>

static bool WriteTGA(const char *path, uint32_t width, uint32_t height, const uint8_t *bgra) {
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
    file.write(reinterpret_cast<const char *>(bgra), width * height * 4);
    return file.good();
}

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <input.blp> <output.tga>\n", argv[0]);
        return 1;
    }

    const char *blpPath = argv[1];
    const char *tgaPath = argv[2];

    CBLPLoader blp;
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
    return 0;
}
