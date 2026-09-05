#pragma once

#include <cstdint>
#include <cstring>
#include <vector>
#include "Gx/Types.h"
#include "Gx/texture/CGxTex.h"
#include "Common/Hashkey.h"

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

// HASHKEY_TEXTUREFILE - hash key for texture cache
class HASHKEY_TEXTUREFILE : public HASHKEY_STR {
public:
    uint8_t texFlags;

    HASHKEY_TEXTUREFILE &operator=(const char *str);
    bool operator==(const char *str);
    bool operator==(const HASHKEY_TEXTUREFILE &other) const;
    HASHKEY_TEXTUREFILE() : texFlags(0) {}
    HASHKEY_TEXTUREFILE(const char *str, uint8_t flags) : texFlags(flags) { m_str = const_cast<char*>(str); }
    HASHKEY_TEXTUREFILE(const char *str, const CGxTexFlags &flags)
        : texFlags(flags.m_filter) { m_str = const_cast<char*>(str); }
};

// CBLPLoader - Unified BLP file loader
// Merged from Gx/texture/CBLPFile and BLPFile implementations
class CBLPLoader {
public:
    CBLPLoader();
    ~CBLPLoader();

    // Load/Close methods (from original CBLPFile)
    int32_t Open(const char *filename);
    int32_t LoadFromBuffer(void *buf);
    void Close();

    // Legacy load methods (convenience wrappers)
    bool LoadFromMemory(const uint8_t *data, size_t size);
    bool LoadFromFile(const char *filePath);

    // Get texture properties
    uint32_t GetWidth() const { return m_width; }
    uint32_t GetHeight() const { return m_height; }
    uint32_t GetMipCount() const { return m_numLevels; }
    uint32_t GetAlphaBits() const { return m_alphaBits; }
    BLPFormat GetFormat() const { return static_cast<BLPFormat>(m_header.type & 0x7); }

    // Get mipmap data
    const uint8_t* GetMipMapData(uint32_t level) const;
    uint32_t GetMipMapSize(uint32_t level) const;

    // Decode methods
    bool DecodeToRGBA(std::vector<uint8_t> &output, uint32_t mipLevel = 0);
    int32_t DecodeMip(uint32_t mipLevel, void *dst, uint32_t dstSize,
                      uint32_t *outWidth, uint32_t *outHeight);
    int32_t LockChain2(char *filename, PIXEL_FORMAT format, MipBits *mipBits,
                       int32_t bestMip, int32_t maxAnisotropy);

    // Check if file is valid
    bool IsValid() const { return m_valid; }

    // Get raw header
    const BLP1Header& GetHeader() const { return m_header; }

    // Get palette (for palette format)
    const uint32_t* GetPalette() const { return m_palette; }

    // Source filename (from original CBLPFile)
    const char *Source;

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
    void *m_data;           // Raw data pointer (for LoadFromBuffer)
    size_t m_dataSize;
    uint32_t m_palette[256];
    bool m_valid;
    bool m_ownsData;        // Whether we own the data and should free it

    // Cached properties
    uint32_t m_width;
    uint32_t m_height;
    uint32_t m_numLevels;
    uint32_t m_alphaBits;
};
