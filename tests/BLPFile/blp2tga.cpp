// blp2tga - BLP to TGA converter
// Usage: blp2tga <input.blp> <output.tga> [--dump-jpeg]

#include "BLPFile/blp.h"
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>

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

static bool WriteJpeg(const char *path, const uint8_t *data, size_t size) {
    std::ofstream file(path, std::ios::binary);
    if (!file.is_open()) return false;
    file.write(reinterpret_cast<const char *>(data), size);
    return file.good();
}

// Extract concatenated JPEG from BLP file
static bool ExtractJpegFromBLP(const char *blpPath, uint32_t mipLevel, const char *outJpegPath) {
    std::ifstream file(blpPath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) return false;

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> data(static_cast<size_t>(size));
    if (!file.read(reinterpret_cast<char*>(data.data()), size)) {
        return false;
    }

    // Parse BLP header
    const BLP1Header *header = reinterpret_cast<const BLP1Header*>(data.data());

    if (header->magic != 0x31504C42) { // "BLP1"
        fprintf(stderr, "Not a BLP1 file\n");
        return false;
    }

    uint32_t compression = header->type & 0x7;
    if (compression != BLP_FORMAT_JPEG) {
        fprintf(stderr, "Not a JPEG BLP file (compression=%u)\n", compression);
        return false;
    }

    // Read JPEG header size (stored right after the 156-byte BLP header)
    uint32_t jpgHeaderSize = *reinterpret_cast<const uint32_t*>(data.data() + sizeof(BLP1Header));

    // JPEG header starts at offset 160 (sizeof(BLP1Header) + 4)
    const uint8_t *jpgHeader = data.data() + sizeof(BLP1Header) + 4;

    // JPEG data starts at mipOffset[mipLevel]
    if (mipLevel >= 16 || header->mipOffsets[mipLevel] == 0) {
        fprintf(stderr, "Invalid mip level %u\n", mipLevel);
        return false;
    }

    const uint8_t *jpgData = data.data() + header->mipOffsets[mipLevel];
    uint32_t jpgDataSize = header->mipSizes[mipLevel];

    printf("JPEG header size: %u bytes\n", jpgHeaderSize);
    printf("JPEG data offset: 0x%x, size: %u bytes\n", header->mipOffsets[mipLevel], jpgDataSize);
    printf("Total JPEG size: %u bytes\n", jpgHeaderSize + jpgDataSize);

    // Concatenate: JPEG header + JPEG data
    std::vector<uint8_t> fullJpeg;
    fullJpeg.reserve(jpgHeaderSize + jpgDataSize);
    fullJpeg.insert(fullJpeg.end(), jpgHeader, jpgHeader + jpgHeaderSize);
    fullJpeg.insert(fullJpeg.end(), jpgData, jpgData + jpgDataSize);

    return WriteJpeg(outJpegPath, fullJpeg.data(), fullJpeg.size());
}

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <input.blp> <output.tga> [--dump-jpeg]\n", argv[0]);
        return 1;
    }

    const char *blpPath = argv[1];
    const char *tgaPath = argv[2];
    bool dumpJpeg = false;

    // Check for --dump-jpeg flag
    for (int i = 3; i < argc; i++) {
        if (strcmp(argv[i], "--dump-jpeg") == 0) {
            dumpJpeg = true;
        }
    }

    // Extract and dump JPEG if requested
    if (dumpJpeg) {
        std::string jpegPath = std::string(tgaPath);
        // Replace .tga extension with _mip0.jpg
        size_t dotPos = jpegPath.rfind('.');
        if (dotPos != std::string::npos) {
            jpegPath = jpegPath.substr(0, dotPos) + "_mip0.jpg";
        } else {
            jpegPath += "_mip0.jpg";
        }

        printf("Extracting JPEG to: %s\n", jpegPath.c_str());
        if (ExtractJpegFromBLP(blpPath, 0, jpegPath.c_str())) {
            printf("JPEG extracted successfully\n");
        } else {
            fprintf(stderr, "Failed to extract JPEG\n");
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
    return 0;
}
