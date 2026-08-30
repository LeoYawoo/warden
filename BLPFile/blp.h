#pragma once

#include <cstdint>
#include <cstring>
#include <vector>

// BLP File Magic Number
constexpr uint32_t BLP_MAGIC = 0x31504C42; // "BLP1"

// BLP Texture Formats
enum BLPFormat : uint32_t {
    BLP_FORMAT_JPEG = 0,
    BLP_FORMAT_PALETTE = 1,
    BLP_FORMAT_DXT1 = 2,
    BLP_FORMAT_DXT3 = 3,
    BLP_FORMAT_DXT5 = 4,
    BLP_FORMAT_UNCOMPRESSED = 5,
};

// BLP Mipmap Info
struct BMipMapInfo {
    uint32_t size;      // Size of compressed data
    uint32_t offset;    // Offset to compressed data
};

// BLP File Header (76 bytes)
#pragma pack(push, 1)
struct BLPHeader {
    uint32_t magic;              // +0: Magic number "BLP1"
    uint32_t version;            // +4: Version (1 = WoW, 2 = WoW 2.x+)
    uint32_t format;             // +8: Texture format (BLPFormat)
    uint32_t flags;              // +12: Flags (1 = wrap, 2 = clamp)
    uint32_t width;              // +16: Texture width
    uint32_t height;             // +20: Texture height
    BMipMapInfo mipmapInfo[16];  // +24: Mipmap info for 16 levels
    uint32_t numMips;            // +152: Number of mipmaps
    uint32_t paletteEntries;     // +156: Number of palette entries (for palette format)
    uint32_t hasAlpha;           // +160: Has alpha channel
};
#pragma pack(pop)

static_assert(sizeof(BLPHeader) == 164, "BLPHeader must be 164 bytes");

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
    BLPFormat GetFormat() const { return static_cast<BLPFormat>(m_header.format); }

    // Get number of mipmaps
    uint32_t GetNumMips() const { return m_header.numMips; }

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
    bool ParseMipMaps(const uint8_t *data, size_t size);
    bool DecodePalette(std::vector<uint8_t> &output, uint32_t mipLevel);
    bool DecodeDXT1(std::vector<uint8_t> &output, uint32_t mipLevel);
    bool DecodeDXT3(std::vector<uint8_t> &output, uint32_t mipLevel);
    bool DecodeDXT5(std::vector<uint8_t> &output, uint32_t mipLevel);
    bool DecodeUncompressed(std::vector<uint8_t> &output, uint32_t mipLevel);

    BLPHeader m_header;
    std::vector<uint8_t> m_fileData;
    std::vector<BMipMapInfo> m_mipMaps;
    uint32_t m_palette[256];
    bool m_valid;
};
