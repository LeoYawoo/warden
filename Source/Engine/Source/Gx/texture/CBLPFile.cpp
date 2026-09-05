#include "CBLPFile.h"
#include "BLPFile/IJG/jpeg_decoder.h"
#include "StormMac/String.h"
#include <cstring>
#include <fstream>
#include <cstdlib>

CBLPFile::CBLPFile()
    : Source(nullptr), m_data(nullptr), m_dataSize(0), m_numLevels(0),
      m_width(0), m_height(0), m_mipCount(0), m_alphaBits(0) {
    memset(&m_header, 0, sizeof(m_header));
}

CBLPFile::~CBLPFile() {
    Close();
}

// HASHKEY_TEXTUREFILE

HASHKEY_TEXTUREFILE &HASHKEY_TEXTUREFILE::operator=(const char *str) {
    m_str = const_cast<char *>(str);
    return *this;
}

bool HASHKEY_TEXTUREFILE::operator==(const char *str) {
    if (!m_str || !str) {
        return m_str == str;
    }
    return strcmp(m_str, str) == 0;
}

bool HASHKEY_TEXTUREFILE::operator==(const HASHKEY_TEXTUREFILE &other) const {
    return (texFlags & 0x3F) == (other.texFlags & 0x3F) && SStrCmpI(m_str, other.m_str, 260) == 0;
}

// CBLPFile

int32_t CBLPFile::Open(const char *filename) {
    if (!filename) return 0;

    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open()) return 0;

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    m_dataSize = static_cast<size_t>(size);
    m_data = malloc(m_dataSize);
    if (!m_data) return 0;

    if (!file.read(static_cast<char*>(m_data), m_dataSize)) {
        free(m_data);
        m_data = nullptr;
        return 0;
    }

    // Parse header
    memcpy(&m_header, m_data, sizeof(BLPHeader));

    if (m_header.magic != 0x31504C42) { // "BLP1"
        free(m_data);
        m_data = nullptr;
        return 0;
    }

    m_width = m_header.width;
    m_height = m_header.height;
    m_alphaBits = m_header.alphaBits;

    // Count mipmaps
    m_numLevels = 0;
    for (uint32_t i = 0; i < 16; ++i) {
        if (m_header.mipSizes[i] > 0) {
            m_numLevels++;
        }
    }
    if (m_numLevels == 0) m_numLevels = 1;

    Source = filename;
    return 1;
}

int32_t CBLPFile::LoadFromBuffer(void *buf) {
    if (!buf) return 0;

    m_data = buf;

    memcpy(&m_header, m_data, sizeof(BLPHeader));

    if (m_header.magic != 0x31504C42) {
        m_data = nullptr;
        return 0;
    }

    m_width = m_header.width;
    m_height = m_header.height;
    m_alphaBits = m_header.alphaBits;

    m_numLevels = 0;
    for (uint32_t i = 0; i < 16; ++i) {
        if (m_header.mipSizes[i] > 0) {
            m_numLevels++;
        }
    }
    if (m_numLevels == 0) m_numLevels = 1;

    return 1;
}

void CBLPFile::Close() {
    if (m_data) {
        free(m_data);
        m_data = nullptr;
    }
}

uint32_t CBLPFile::GetWidth() const {
    return m_width;
}

uint32_t CBLPFile::GetHeight() const {
    return m_height;
}

uint32_t CBLPFile::GetMipCount() const {
    return m_numLevels;
}

uint32_t CBLPFile::GetAlphaBits() const {
    return m_alphaBits;
}

int32_t CBLPFile::DecodeMip(uint32_t mipLevel, void *dst, uint32_t dstSize, uint32_t *outWidth, uint32_t *outHeight) {
    if (!m_data || mipLevel >= 16) return 0;

    uint32_t w = m_header.width >> mipLevel;
    uint32_t h = m_header.height >> mipLevel;
    if (w == 0) w = 1;
    if (h == 0) h = 1;

    if (outWidth) *outWidth = w;
    if (outHeight) *outHeight = h;

    if (!dst) return 1; // Just query dimensions

    uint32_t compression = m_header.type & 0x7;

    if (compression == 0) {
        // JPEG-BLP: concatenate JPEG header + JPEG data from mipmap offset
        const uint8_t *fileData = static_cast<const uint8_t*>(m_data);

        // Read JPEG header size (stored right after the 156-byte BLP header)
        uint32_t jpgHeaderSize = *reinterpret_cast<const uint32_t*>(fileData + sizeof(BLPHeader));

        // JPEG header starts at offset 160 (sizeof(BLPHeader) + 4)
        const uint8_t *jpgHeader = fileData + sizeof(BLPHeader) + 4;

        // JPEG data starts at mipOffset[mipLevel]
        const uint8_t *jpgData = fileData + m_header.mipOffsets[mipLevel];
        uint32_t jpgDataSize = m_header.mipSizes[mipLevel];

        // Concatenate: JPEG header + JPEG data
        std::vector<uint8_t> fullJpeg;
        fullJpeg.reserve(jpgHeaderSize + jpgDataSize);
        fullJpeg.insert(fullJpeg.end(), jpgHeader, jpgHeader + jpgHeaderSize);
        fullJpeg.insert(fullJpeg.end(), jpgData, jpgData + jpgDataSize);

        JpegDecoder decoder;
        decoder.SetDimensions(m_header.width >> mipLevel, m_header.height >> mipLevel);
        uint32_t jpegW = 0, jpegH = 0;
        std::vector<uint8_t> jpegOutput;
        if (!decoder.Decode(fullJpeg.data(), fullJpeg.size(), jpegOutput, jpegW, jpegH)) {
            return 0;
        }
        uint32_t copySize = std::min(dstSize, static_cast<uint32_t>(jpegOutput.size()));
        memcpy(dst, jpegOutput.data(), copySize);
        if (outWidth) *outWidth = jpegW;
        if (outHeight) *outHeight = jpegH;
        return 1;
    } else if (compression == 1) {
        // Palette
        const uint8_t *fileData = static_cast<const uint8_t*>(m_data);
        uint32_t *palette = reinterpret_cast<uint32_t*>(const_cast<uint8_t*>(fileData + sizeof(BLPHeader)));
        uint8_t *out = static_cast<uint8_t*>(dst);
        uint8_t *src = const_cast<uint8_t*>(fileData + m_header.mipOffsets[mipLevel]);
        uint32_t srcSize = m_header.mipSizes[mipLevel];
        for (uint32_t i = 0; i < w * h && i < srcSize; ++i) {
            uint32_t color = palette[src[i]];
            out[i * 4 + 0] = (color >> 16) & 0xFF;
            out[i * 4 + 1] = (color >> 8) & 0xFF;
            out[i * 4 + 2] = color & 0xFF;
            out[i * 4 + 3] = (color >> 24) & 0xFF;
        }
        return 1;
    } else if (compression == 4) {
        // DXT5
        const uint8_t *fileData = static_cast<const uint8_t*>(m_data);
        const uint8_t *ptr = fileData + m_header.mipOffsets[mipLevel];
        uint8_t *out = static_cast<uint8_t*>(dst);
        for (uint32_t y = 0; y < h; y += 4) {
            for (uint32_t x = 0; x < w; x += 4) {
                uint8_t a0 = ptr[0], a1 = ptr[1];
                uint64_t abits = *reinterpret_cast<const uint16_t*>(ptr+2) |
                    (static_cast<uint64_t>(*reinterpret_cast<const uint16_t*>(ptr+4)) << 16) |
                    (static_cast<uint64_t>(*reinterpret_cast<const uint16_t*>(ptr+6)) << 32);
                ptr += 8;

                uint16_t c0 = *reinterpret_cast<const uint16_t*>(ptr);
                uint16_t c1 = *reinterpret_cast<const uint16_t*>(ptr+2);
                uint32_t idx = *reinterpret_cast<const uint32_t*>(ptr+4);
                ptr += 8;

                uint8_t r0=((c0>>11)&0x1F)<<3, g0=((c0>>5)&0x3F)<<2, b0=(c0&0x1F)<<3;
                uint8_t r1=((c1>>11)&0x1F)<<3, g1=((c1>>5)&0x3F)<<2, b1=(c1&0x1F)<<3;

                for (uint32_t py=0; py<4 && (y+py)<h; ++py) {
                    for (uint32_t px=0; px<4 && (x+px)<w; ++px) {
                        uint32_t ci = (idx >> ((py*4+px)*2)) & 3;
                        uint32_t ai = py*4+px;
                        uint8_t alpha;
                        if (a0 > a1)
                            alpha = (uint8_t)(((6-ai%3)*a0 + (ai%3+1)*a1+3)/6);
                        else if (ai == 0) alpha = a0;
                        else if (ai == 1) alpha = a1;
                        else alpha = (uint8_t)(((2-ai%3)*a0 + (ai%3-1)*a1+1)/4);

                        uint8_t r,g,b;
                        switch(ci) {
                            case 0: r=r0;g=g0;b=b0;break;
                            case 1: r=r1;g=g1;b=b1;break;
                            case 2: r=(2*r0+r1)/3;g=(2*g0+g1)/3;b=(2*b0+b1)/3;break;
                            default: r=(r0+2*r1)/3;g=(g0+2*g1)/3;b=(b0+2*b1)/3;break;
                        }
                        uint32_t pi = ((y+py)*w+(x+px))*4;
                        out[pi]=r; out[pi+1]=g; out[pi+2]=b; out[pi+3]=alpha;
                    }
                }
            }
        }
        return 1;
    }

    return 0;
}

int32_t CBLPFile::LockChain2(char * /*filename*/, PIXEL_FORMAT /*format*/, MipBits * /*mipBits*/, int32_t /*bestMip*/, int32_t /*maxAnisotropy*/) {
    // TODO: Reverse engineer from IDA
    return 0;
}
