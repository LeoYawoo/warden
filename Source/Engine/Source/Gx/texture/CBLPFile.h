#pragma once
// TODO: Reverse engineer from IDA

#include <cstdint>
#include <string>
#include "../Types.h"
#include "Common/Hashkey.h"
#include "CGxTex.h"

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

// BLP file header
struct BLPHeader {
    uint32_t signature;
    uint32_t version;
    uint8_t compression;
    uint8_t alphaSize;
    uint8_t preferredFormat;
    uint8_t hasMips;
    uint32_t width;
    uint32_t height;
    uint32_t mipOffsets[16];
    uint32_t mipSizes[16];
};

// CBLPFile - BLP texture file loader
class CBLPFile {
public:
    CBLPFile();
    ~CBLPFile();

    int32_t Open(const char *filename);
    int32_t LoadFromBuffer(void *buf);
    void Close();

    uint32_t GetWidth() const;
    uint32_t GetHeight() const;
    uint32_t GetMipCount() const;
    uint32_t GetAlphaBits() const;

    int32_t DecodeMip(uint32_t mipLevel, void *dst, uint32_t dstSize, uint32_t *outWidth, uint32_t *outHeight);
    int32_t LockChain2(char *filename, PIXEL_FORMAT format, MipBits *mipBits, int32_t bestMip, int32_t maxAnisotropy);

    // IDA reverse-engineered members
    const char *Source;
    BLPHeader m_header;
    void *m_data;
    uint32_t m_numLevels;
    uint32_t m_width;
    uint32_t m_height;
    uint32_t m_mipCount;
    uint32_t m_alphaBits;
};
