#include "blp.h"
#include "IJG/jpeg_decoder.h"
#include <fstream>

CBLPLoader::CBLPLoader() : m_valid(false) {
    std::memset(&m_header, 0, sizeof(m_header));
    std::memset(m_palette, 0, sizeof(m_palette));
}

CBLPLoader::~CBLPLoader() {
}

bool CBLPLoader::LoadFromMemory(const uint8_t *data, size_t size) {
    if (!data || size < sizeof(BLP1Header)) {
        return false;
    }

    m_fileData.assign(data, data + size);
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

    return ParseHeader(m_fileData.data(), m_fileData.size());
}

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

uint32_t CBLPLoader::GetNumMips() const {
    if (!m_valid) return 0;

    // Count valid mipmaps
    uint32_t count = 0;
    for (uint32_t i = 0; i < 16; ++i) {
        if (m_header.mipSizes[i] > 0 && m_header.mipOffsets[i] > 0) {
            count++;
        } else {
            break;
        }
    }
    return count;
}

const uint8_t* CBLPLoader::GetMipMapData(uint32_t level) const {
    if (!m_valid || level >= 16 || m_header.mipOffsets[level] == 0) {
        return nullptr;
    }
    if (m_header.mipOffsets[level] >= m_fileData.size()) {
        return nullptr;
    }
    return m_fileData.data() + m_header.mipOffsets[level];
}

uint32_t CBLPLoader::GetMipMapSize(uint32_t level) const {
    if (!m_valid || level >= 16) {
        return 0;
    }
    return m_header.mipSizes[level];
}

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
