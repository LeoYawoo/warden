#pragma once

#include <cstdint>
#include <cstring>
#include <vector>

// BLP Texture Formats (compression field, low 3 bits)
enum BLPFormat : uint32_t {
    BLP_FORMAT_JPEG = 0,
    BLP_FORMAT_PALETTE = 1,
    BLP_FORMAT_DXT1 = 2,
    BLP_FORMAT_DXT3 = 3,
    BLP_FORMAT_DXT5 = 4,
    BLP_FORMAT_UNCOMPRESSED = 5,
};

// BLP1 file header (156 bytes)
// Reference: gowarcraft3, openwarcraft3
// Note: Same as Gx/texture/CBLPFile.h BLPHeader
#pragma pack(push, 1)
struct BLP1Header {
    uint32_t magic;           // +0:   "BLP1"
    uint32_t type;            // +4:   0=JPG, 1=Paletted
    uint32_t alphaBits;       // +8:   0x08=has alpha, 0x00=no alpha
    uint32_t width;           // +12
    uint32_t height;          // +16
    uint32_t extra;           // +20:  flags (3/4/5)
    uint32_t hasMipmaps;      // +24:  always 1
    uint32_t mipOffsets[16];  // +28:  file offsets to mip data
    uint32_t mipSizes[16];    // +92:  sizes of mip data
};
#pragma pack(pop)

// CBLPLoader - Standalone BLP file loader with full format support
// This is a separate implementation from Gx/texture/CBLPFile
class CBLPLoader {
public:
    CBLPLoader();
    ~CBLPLoader();

    // Load BLP file from memory
    bool LoadFromMemory(const uint8_t *data, size_t size);

    // Load BLP file from file path
    bool LoadFromFile(const char *filePath);

    // Get texture dimensions
    uint32_t GetWidth() const { return m_header.width; }
    uint32_t GetHeight() const { return m_header.height; }

    // Get texture format
    BLPFormat GetFormat() const { return static_cast<BLPFormat>(m_header.type & 0x7); }

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
    const BLP1Header& GetHeader() const { return m_header; }

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

    BLP1Header m_header;
    std::vector<uint8_t> m_fileData;
    uint32_t m_palette[256];
    bool m_valid;
};
