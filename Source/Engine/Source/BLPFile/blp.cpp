#include "blp.h"
#include "IJG/jpeg_decoder.h"
#include "StormMac/String.h"
#include <fstream>
#include <algorithm>
#include <cstdlib>

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

CBLPLoader::CBLPLoader()
    : Source(nullptr), m_data(nullptr), m_dataSize(0), m_valid(false),
      m_ownsData(false), m_width(0), m_height(0), m_numLevels(0), m_alphaBits(0) {
    std::memset(&m_header, 0, sizeof(m_header));
    std::memset(m_palette, 0, sizeof(m_palette));
}

CBLPLoader::~CBLPLoader() {
    Close();
}

// ============================================================
// Load/Close methods (from original CBLPFile)
// ============================================================

int32_t CBLPLoader::Open(const char *filename) {
    if (!filename) return 0;

    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open()) return 0;

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    m_dataSize = static_cast<size_t>(size);
    m_data = std::malloc(m_dataSize);
    if (!m_data) return 0;

    if (!file.read(static_cast<char*>(m_data), m_dataSize)) {
        std::free(m_data);
        m_data = nullptr;
        return 0;
    }

    m_ownsData = true;

    // Parse header
    std::memcpy(&m_header, m_data, sizeof(BLP1Header));

    if (m_header.magic != 0x31504C42) { // "BLP1"
        std::free(m_data);
        m_data = nullptr;
        m_ownsData = false;
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

    // Parse palette if needed
    uint32_t compressionType = m_header.type & 0x7;
    if (compressionType == BLP_FORMAT_PALETTE && m_header.type > 0) {
        uint32_t paletteSize = m_header.type * sizeof(uint32_t);
        if (sizeof(BLP1Header) + paletteSize <= m_dataSize) {
            std::memcpy(m_palette, static_cast<uint8_t*>(m_data) + sizeof(BLP1Header), paletteSize);
        }
    }

    Source = filename;
    m_valid = true;
    return 1;
}

int32_t CBLPLoader::LoadFromBuffer(void *buf) {
    if (!buf) return 0;

    m_data = buf;
    m_ownsData = false;

    std::memcpy(&m_header, m_data, sizeof(BLP1Header));

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

    // Parse palette if needed
    uint32_t compressionType = m_header.type & 0x7;
    if (compressionType == BLP_FORMAT_PALETTE && m_header.type > 0) {
        uint32_t paletteSize = m_header.type * sizeof(uint32_t);
        if (sizeof(BLP1Header) + paletteSize <= m_dataSize) {
            std::memcpy(m_palette, static_cast<uint8_t*>(m_data) + sizeof(BLP1Header), paletteSize);
        }
    }

    m_valid = true;
    return 1;
}

void CBLPLoader::Close() {
    if (m_data && m_ownsData) {
        std::free(m_data);
    }
    m_data = nullptr;
    m_dataSize = 0;
    m_ownsData = false;
    m_valid = false;
}

// ============================================================
// Legacy load methods (convenience wrappers)
// ============================================================

bool CBLPLoader::LoadFromMemory(const uint8_t *data, size_t size) {
    if (!data || size < sizeof(BLP1Header)) {
        return false;
    }

    m_fileData.assign(data, data + size);
    m_data = m_fileData.data();
    m_dataSize = size;
    m_ownsData = false;

    return ParseHeader(data, size);
}

bool CBLPLoader::LoadFromFile(const char *filePath) {
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        return false;
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    m_fileData.resize(static_cast<size_t>(size));
    if (!file.read(reinterpret_cast<char*>(m_fileData.data()), size)) {
        return false;
    }

    m_data = m_fileData.data();
    m_dataSize = size;
    m_ownsData = false;

    return ParseHeader(m_fileData.data(), m_fileData.size());
}

// ============================================================
// Header parsing
// ============================================================

bool CBLPLoader::ParseHeader(const uint8_t *data, size_t size) {
    std::memcpy(&m_header, data, sizeof(BLP1Header));

    // Validate magic number
    if (m_header.magic != 0x31504C42) { // "BLP1"
        m_valid = false;
        return false;
    }

    // Validate compression type (low 3 bits)
    uint32_t compressionType = m_header.type & 0x7;
    if (compressionType > BLP_FORMAT_UNCOMPRESSED) {
        m_valid = false;
        return false;
    }

    // Validate dimensions
    if (m_header.width == 0 || m_header.height == 0) {
        m_valid = false;
        return false;
    }

    m_width = m_header.width;
    m_height = m_header.height;
    m_alphaBits = m_header.alphaBits;

    // Count mipmaps
    m_numLevels = 0;
    for (uint32_t i = 0; i < 16; ++i) {
        if (m_header.mipSizes[i] > 0 && m_header.mipOffsets[i] > 0) {
            m_numLevels++;
        } else {
            break;
        }
    }
    if (m_numLevels == 0) m_numLevels = 1;

    // Parse palette if needed
    if (compressionType == BLP_FORMAT_PALETTE && m_header.type > 0) {
        uint32_t paletteSize = m_header.type * sizeof(uint32_t);
        if (sizeof(BLP1Header) + paletteSize <= size) {
            std::memcpy(m_palette, data + sizeof(BLP1Header), paletteSize);
        }
    }

    m_valid = true;
    return true;
}

// ============================================================
// Mipmap data access
// ============================================================

const uint8_t* CBLPLoader::GetMipMapData(uint32_t level) const {
    if (!m_valid || !m_data || level >= 16 || m_header.mipOffsets[level] == 0) {
        return nullptr;
    }
    if (m_header.mipOffsets[level] >= m_dataSize) {
        return nullptr;
    }
    return static_cast<const uint8_t*>(m_data) + m_header.mipOffsets[level];
}

uint32_t CBLPLoader::GetMipMapSize(uint32_t level) const {
    if (!m_valid || level >= 16) {
        return 0;
    }
    return m_header.mipSizes[level];
}

// ============================================================
// Decode methods
// ============================================================

bool CBLPLoader::DecodeToRGBA(std::vector<uint8_t> &output, uint32_t mipLevel) {
    if (!m_valid) {
        return false;
    }

    uint32_t compressionType = m_header.type & 0x7;
    switch (compressionType) {
        case BLP_FORMAT_JPEG:
            return DecodeJPEG(output, mipLevel);
        case BLP_FORMAT_PALETTE:
            return DecodePalette(output, mipLevel);
        case BLP_FORMAT_DXT1:
            return DecodeDXT1(output, mipLevel);
        case BLP_FORMAT_DXT3:
            return DecodeDXT3(output, mipLevel);
        case BLP_FORMAT_DXT5:
            return DecodeDXT5(output, mipLevel);
        case BLP_FORMAT_UNCOMPRESSED:
            return DecodeUncompressed(output, mipLevel);
        default:
            return false;
    }
}

int32_t CBLPLoader::DecodeMip(uint32_t mipLevel, void *dst, uint32_t dstSize,
                              uint32_t *outWidth, uint32_t *outHeight) {
    if (!m_data || mipLevel >= 16) return 0;

    uint32_t w = m_header.width >> mipLevel;
    uint32_t h = m_header.height >> mipLevel;
    if (w == 0) w = 1;
    if (h == 0) h = 1;

    if (outWidth) *outWidth = w;
    if (outHeight) *outHeight = h;

    if (!dst) return 1; // Just query dimensions

    uint32_t compression = m_header.type & 0x7;

    if (compression == BLP_FORMAT_JPEG) {
        // JPEG-BLP: concatenate JPEG header + JPEG data from mipmap offset
        const uint8_t *fileData = static_cast<const uint8_t*>(m_data);

        // Read JPEG header size (stored right after the 156-byte BLP header)
        uint32_t jpgHeaderSize = *reinterpret_cast<const uint32_t*>(fileData + sizeof(BLP1Header));

        // JPEG header starts at offset 160 (sizeof(BLP1Header) + 4)
        const uint8_t *jpgHeader = fileData + sizeof(BLP1Header) + 4;

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
        std::memcpy(dst, jpegOutput.data(), copySize);
        if (outWidth) *outWidth = jpegW;
        if (outHeight) *outHeight = jpegH;
        return 1;
    } else if (compression == BLP_FORMAT_PALETTE) {
        // Palette
        const uint8_t *fileData = static_cast<const uint8_t*>(m_data);
        uint32_t *palette = reinterpret_cast<uint32_t*>(const_cast<uint8_t*>(fileData + sizeof(BLP1Header)));
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
    } else if (compression == BLP_FORMAT_DXT5) {
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
                            alpha = static_cast<uint8_t>(((6-ai%3)*a0 + (ai%3+1)*a1+3)/6);
                        else if (ai == 0) alpha = a0;
                        else if (ai == 1) alpha = a1;
                        else alpha = static_cast<uint8_t>(((2-ai%3)*a0 + (ai%3-1)*a1+1)/4);

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

int32_t CBLPLoader::LockChain2(char * /*filename*/, PIXEL_FORMAT /*format*/, MipBits * /*mipBits*/,
                               int32_t /*bestMip*/, int32_t /*maxAnisotropy*/) {
    // TODO: Reverse engineer from IDA
    return 0;
}

// ============================================================
// Internal decode methods
// ============================================================

bool CBLPLoader::DecodePalette(std::vector<uint8_t> &output, uint32_t mipLevel) {
    const uint8_t *data = GetMipMapData(mipLevel);
    uint32_t dataSize = GetMipMapSize(mipLevel);

    if (!data || dataSize == 0) {
        return false;
    }

    uint32_t width = m_header.width >> mipLevel;
    uint32_t height = m_header.height >> mipLevel;
    if (width == 0) width = 1;
    if (height == 0) height = 1;

    uint32_t numPixels = width * height;
    output.resize(numPixels * 4);

    for (uint32_t i = 0; i < numPixels; ++i) {
        uint8_t index = data[i];
        uint32_t color = m_palette[index];

        output[i * 4 + 0] = (color >> 16) & 0xFF;  // R
        output[i * 4 + 1] = (color >> 8) & 0xFF;   // G
        output[i * 4 + 2] = color & 0xFF;           // B
        output[i * 4 + 3] = (color >> 24) & 0xFF;  // A
    }

    return true;
}

bool CBLPLoader::DecodeDXT1(std::vector<uint8_t> &output, uint32_t mipLevel) {
    const uint8_t *data = GetMipMapData(mipLevel);
    uint32_t dataSize = GetMipMapSize(mipLevel);

    if (!data || dataSize == 0) {
        return false;
    }

    uint32_t width = m_header.width >> mipLevel;
    uint32_t height = m_header.height >> mipLevel;
    if (width == 0) width = 1;
    if (height == 0) height = 1;

    output.resize(width * height * 4);

    const uint8_t *ptr = data;
    for (uint32_t y = 0; y < height; y += 4) {
        for (uint32_t x = 0; x < width; x += 4) {
            uint16_t color0 = *reinterpret_cast<const uint16_t*>(ptr);
            uint16_t color1 = *reinterpret_cast<const uint16_t*>(ptr + 2);
            uint32_t indices = *reinterpret_cast<const uint32_t*>(ptr + 4);
            ptr += 8;

            uint8_t r0 = ((color0 >> 11) & 0x1F) << 3;
            uint8_t g0 = ((color0 >> 5) & 0x3F) << 2;
            uint8_t b0 = (color0 & 0x1F) << 3;
            uint8_t r1 = ((color1 >> 11) & 0x1F) << 3;
            uint8_t g1 = ((color1 >> 5) & 0x3F) << 2;
            uint8_t b1 = (color1 & 0x1F) << 3;

            for (uint32_t py = 0; py < 4 && (y + py) < height; ++py) {
                for (uint32_t px = 0; px < 4 && (x + px) < width; ++px) {
                    uint32_t idx = (indices >> ((py * 4 + px) * 2)) & 0x3;
                    uint8_t r, g, b, a;

                    if (color0 > color1) {
                        switch (idx) {
                            case 0: r = r0; g = g0; b = b0; a = 255; break;
                            case 1: r = r1; g = g1; b = b1; a = 255; break;
                            case 2: r = (2*r0+r1)/3; g = (2*g0+g1)/3; b = (2*b0+b1)/3; a = 255; break;
                            case 3: r = (r0+2*r1)/3; g = (g0+2*g1)/3; b = (b0+2*b1)/3; a = 255; break;
                        }
                    } else {
                        switch (idx) {
                            case 0: r = r0; g = g0; b = b0; a = 255; break;
                            case 1: r = r1; g = g1; b = b1; a = 255; break;
                            case 2: r = (r0+r1)/2; g = (g0+g1)/2; b = (b0+b1)/2; a = 255; break;
                            case 3: r = 0; g = 0; b = 0; a = 0; break;
                        }
                    }

                    uint32_t pixelIdx = ((y + py) * width + (x + px)) * 4;
                    output[pixelIdx + 0] = r;
                    output[pixelIdx + 1] = g;
                    output[pixelIdx + 2] = b;
                    output[pixelIdx + 3] = a;
                }
            }
        }
    }
    return true;
}

bool CBLPLoader::DecodeDXT3(std::vector<uint8_t> &output, uint32_t mipLevel) {
    const uint8_t *data = GetMipMapData(mipLevel);
    uint32_t dataSize = GetMipMapSize(mipLevel);

    if (!data || dataSize == 0) return false;

    uint32_t width = m_header.width >> mipLevel;
    uint32_t height = m_header.height >> mipLevel;
    if (width == 0) width = 1;
    if (height == 0) height = 1;

    output.resize(width * height * 4);
    const uint8_t *ptr = data;

    for (uint32_t y = 0; y < height; y += 4) {
        for (uint32_t x = 0; x < width; x += 4) {
            uint64_t alphaBlock = *reinterpret_cast<const uint64_t*>(ptr);
            ptr += 8;

            uint16_t color0 = *reinterpret_cast<const uint16_t*>(ptr);
            uint16_t color1 = *reinterpret_cast<const uint16_t*>(ptr + 2);
            uint32_t indices = *reinterpret_cast<const uint32_t*>(ptr + 4);
            ptr += 8;

            uint8_t r0 = ((color0 >> 11) & 0x1F) << 3;
            uint8_t g0 = ((color0 >> 5) & 0x3F) << 2;
            uint8_t b0 = (color0 & 0x1F) << 3;
            uint8_t r1 = ((color1 >> 11) & 0x1F) << 3;
            uint8_t g1 = ((color1 >> 5) & 0x3F) << 2;
            uint8_t b1 = (color1 & 0x1F) << 3;

            for (uint32_t py = 0; py < 4 && (y + py) < height; ++py) {
                for (uint32_t px = 0; px < 4 && (x + px) < width; ++px) {
                    uint32_t colorIdx = (indices >> ((py * 4 + px) * 2)) & 0x3;
                    uint8_t alpha = static_cast<uint8_t>(((alphaBlock >> (py * 4 + px) * 4) & 0xF) * 17);

                    uint8_t r, g, b;
                    switch (colorIdx) {
                        case 0: r = r0; g = g0; b = b0; break;
                        case 1: r = r1; g = g1; b = b1; break;
                        case 2: r = (2*r0+r1)/3; g = (2*g0+g1)/3; b = (2*b0+b1)/3; break;
                        case 3: r = (r0+2*r1)/3; g = (g0+2*g1)/3; b = (b0+2*b1)/3; break;
                    }

                    uint32_t pixelIdx = ((y + py) * width + (x + px)) * 4;
                    output[pixelIdx + 0] = r;
                    output[pixelIdx + 1] = g;
                    output[pixelIdx + 2] = b;
                    output[pixelIdx + 3] = alpha;
                }
            }
        }
    }
    return true;
}

bool CBLPLoader::DecodeDXT5(std::vector<uint8_t> &output, uint32_t mipLevel) {
    const uint8_t *data = GetMipMapData(mipLevel);
    uint32_t dataSize = GetMipMapSize(mipLevel);

    if (!data || dataSize == 0) return false;

    uint32_t width = m_header.width >> mipLevel;
    uint32_t height = m_header.height >> mipLevel;
    if (width == 0) width = 1;
    if (height == 0) height = 1;

    output.resize(width * height * 4);
    const uint8_t *ptr = data;

    for (uint32_t y = 0; y < height; y += 4) {
        for (uint32_t x = 0; x < width; x += 4) {
            uint8_t alpha0 = ptr[0];
            uint8_t alpha1 = ptr[1];
            uint64_t alphaBits = *reinterpret_cast<const uint16_t*>(ptr + 2) |
                                 (static_cast<uint64_t>(*reinterpret_cast<const uint16_t*>(ptr + 4)) << 16) |
                                 (static_cast<uint64_t>(*reinterpret_cast<const uint16_t*>(ptr + 6)) << 32);
            ptr += 8;

            uint16_t color0 = *reinterpret_cast<const uint16_t*>(ptr);
            uint16_t color1 = *reinterpret_cast<const uint16_t*>(ptr + 2);
            uint32_t indices = *reinterpret_cast<const uint32_t*>(ptr + 4);
            ptr += 8;

            uint8_t r0 = ((color0 >> 11) & 0x1F) << 3;
            uint8_t g0 = ((color0 >> 5) & 0x3F) << 2;
            uint8_t b0 = (color0 & 0x1F) << 3;
            uint8_t r1 = ((color1 >> 11) & 0x1F) << 3;
            uint8_t g1 = ((color1 >> 5) & 0x3F) << 2;
            uint8_t b1 = (color1 & 0x1F) << 3;

            for (uint32_t py = 0; py < 4 && (y + py) < height; ++py) {
                for (uint32_t px = 0; px < 4 && (x + px) < width; ++px) {
                    uint32_t colorIdx = (indices >> ((py * 4 + px) * 2)) & 0x3;
                    uint32_t alphaIdx = py * 4 + px;

                    uint8_t alpha;
                    if (alpha0 > alpha1) {
                        alpha = static_cast<uint8_t>(((6 - alphaIdx % 3) * alpha0 + (alphaIdx % 3 + 1) * alpha1 + 3) / 6);
                    } else {
                        if (alphaIdx == 0) alpha = alpha0;
                        else if (alphaIdx == 1) alpha = alpha1;
                        else alpha = static_cast<uint8_t>(((2 - alphaIdx % 3) * alpha0 + (alphaIdx % 3 - 1) * alpha1 + 1) / 4);
                    }

                    uint8_t r, g, b;
                    switch (colorIdx) {
                        case 0: r = r0; g = g0; b = b0; break;
                        case 1: r = r1; g = g1; b = b1; break;
                        case 2: r = (2*r0+r1)/3; g = (2*g0+g1)/3; b = (2*b0+b1)/3; break;
                        case 3: r = (r0+2*r1)/3; g = (g0+2*g1)/3; b = (b0+2*b1)/3; break;
                    }

                    uint32_t pixelIdx = ((y + py) * width + (x + px)) * 4;
                    output[pixelIdx + 0] = r;
                    output[pixelIdx + 1] = g;
                    output[pixelIdx + 2] = b;
                    output[pixelIdx + 3] = alpha;
                }
            }
        }
    }
    return true;
}

bool CBLPLoader::DecodeUncompressed(std::vector<uint8_t> &output, uint32_t mipLevel) {
    const uint8_t *data = GetMipMapData(mipLevel);
    uint32_t dataSize = GetMipMapSize(mipLevel);

    if (!data || dataSize == 0) return false;

    uint32_t width = m_header.width >> mipLevel;
    uint32_t height = m_header.height >> mipLevel;
    if (width == 0) width = 1;
    if (height == 0) height = 1;

    output.resize(width * height * 4);

    for (uint32_t y = 0; y < height; ++y) {
        for (uint32_t x = 0; x < width; ++x) {
            uint32_t srcIdx = (y * width + x) * 4;
            if (srcIdx + 3 < dataSize) {
                output[srcIdx + 0] = data[srcIdx + 2];  // R
                output[srcIdx + 1] = data[srcIdx + 1];  // G
                output[srcIdx + 2] = data[srcIdx + 0];  // B
                output[srcIdx + 3] = data[srcIdx + 3];  // A
            }
        }
    }
    return true;
}

bool CBLPLoader::DecodeJPEG(std::vector<uint8_t> &output, uint32_t mipLevel) {
    const uint8_t *data = GetMipMapData(mipLevel);
    uint32_t dataSize = GetMipMapSize(mipLevel);

    if (!data || dataSize == 0) {
        return false;
    }

    JpegDecoder decoder;
    uint32_t width = 0, height = 0;

    if (!decoder.Decode(data, dataSize, output, width, height)) {
        return false;
    }

    return true;
}
