#pragma once

#include <cstdint>
#include <cstring>
#include <vector>

// BLP File Magic Number
constexpr uint32_t BLP_MAGIC = 0x31504C42; // "BLP1"

// BLP Texture Formats (compression field, low 3 bits)
enum BLPFormat : uint32_t {
    BLP_FORMAT_JPEG = 0,
    BLP_FORMAT_PALETTE = 1,
    BLP_FORMAT_DXT1 = 2,
    BLP_FORMAT_DXT3 = 3,
    BLP_FORMAT_DXT5 = 4,
    BLP_FORMAT_UNCOMPRESSED = 5,
};

// BLP File Header (148 bytes)
// Reverse engineered from IDA - matches Gx/texture/CBLPFile.h
#pragma pack(push, 1)
struct BLPHeader {
    uint32_t signature;         // +0:   Magic number "BLP1"
    uint32_t version;           // +4:   Version (0 = WoW)
    uint8_t compression;        // +8:   Compression type (BLPFormat, low 3 bits)
    uint8_t alphaSize;          // +9:   Alpha channel bits
    uint8_t preferredFormat;    // +10:  Preferred pixel format
    uint8_t hasMips;            // +11:  Has mipmaps (bit 4 = has mips)
    uint32_t width;             // +12:  Texture width
    uint32_t height;            // +16:  Texture height
    uint32_t mipOffsets[16];    // +20:  Mipmap data offsets
    uint32_t mipSizes[16];      // +84:  Mipmap data sizes
};
#pragma pack(pop)

// BLP File class
class CBLPFile {
public:
    CBLPFile();
    ~CBLPFile();

    // Load BLP file from memory
    bool LoadFromMemory(const uint8_t *data, size_t size);

    // Load BLP file from file path
    bool LoadFromFile(const char *filePath);

    // Get texture dimensions
    uint32_t GetWidth() const { return m_header.width; }
    uint32_t GetHeight() const { return m_header.height; }

    // Get texture format
    BLPFormat GetFormat() const { return static_cast<BLPFormat>(m_header.compression & 0x7); }

    // Get number of mipmaps
    uint32_t GetNumMips() const;

    // Get mipmap data
    const uint8_t* GetMipMapData(uint32_t level) const;

    // Get mipmap size
    uint32_t GetMipMapSize(uint32_t level) const;

    // Decode texture to RGBA format
    bool DecodeToRGBA(std::vector<uint8_t> &output, uint32_t mipLevel = 0);

    // Check if file is valid
    bool IsValid() const { return m_valid; }

    // Get raw header
    const BLPHeader& GetHeader() const { return m_header; }

    // Get palette (for palette format)
    const uint32_t* GetPalette() const { return m_palette; }

private:
    bool ParseHeader(const uint8_t *data, size_t size);
    bool DecodePalette(std::vector<uint8_t> &output, uint32_t mipLevel);
    bool DecodeDXT1(std::vector<uint8_t> &output, uint32_t mipLevel);
    bool DecodeDXT3(std::vector<uint8_t> &output, uint32_t mipLevel);
    bool DecodeDXT5(std::vector<uint8_t> &output, uint32_t mipLevel);
    bool DecodeUncompressed(std::vector<uint8_t> &output, uint32_t mipLevel);
    bool DecodeJPEG(std::vector<uint8_t> &output, uint32_t mipLevel);

    BLPHeader m_header;
    std::vector<uint8_t> m_fileData;
    uint32_t m_palette[256];
    bool m_valid;
};
