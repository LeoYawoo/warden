#include "blp.h"
#include "IJG/jmemstorm.h"
#include <fstream>

CBLPFile::CBLPFile() : m_valid(false) {
    std::memset(&m_header, 0, sizeof(m_header));
    std::memset(m_palette, 0, sizeof(m_palette));
}

CBLPFile::~CBLPFile() {
}

bool CBLPFile::LoadFromMemory(const uint8_t *data, size_t size) {
    if (!data || size < sizeof(BLPHeader)) {
        return false;
    }

    m_fileData.assign(data, data + size);
    return ParseHeader(data, size);
}

bool CBLPFile::LoadFromFile(const char *filePath) {
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

bool CBLPFile::ParseHeader(const uint8_t *data, size_t size) {
    std::memcpy(&m_header, data, sizeof(BLPHeader));

    // Validate magic number
    if (m_header.magic != BLP_MAGIC) {
        m_valid = false;
        return false;
    }

    // Validate format
    if (m_header.format > BLP_FORMAT_UNCOMPRESSED) {
        m_valid = false;
        return false;
    }

    // Validate dimensions
    if (m_header.width == 0 || m_header.height == 0) {
        m_valid = false;
        return false;
    }

    // Parse mipmaps
    if (!ParseMipMaps(data, size)) {
        m_valid = false;
        return false;
    }

    // Parse palette if needed
    if (m_header.format == BLP_FORMAT_PALETTE && m_header.paletteEntries > 0) {
        uint32_t paletteSize = m_header.paletteEntries * sizeof(uint32_t);
        if (sizeof(BLPHeader) + paletteSize <= size) {
            std::memcpy(m_palette, data + sizeof(BLPHeader), paletteSize);
        }
    }

    m_valid = true;
    return true;
}

bool CBLPFile::ParseMipMaps(const uint8_t *data, size_t size) {
    m_mipMaps.clear();
    m_mipMaps.reserve(m_header.numMips);

    for (uint32_t i = 0; i < m_header.numMips && i < 16; ++i) {
        const BMipMapInfo &info = m_header.mipmapInfo[i];
        if (info.offset + info.size > size) {
            return false;
        }
        m_mipMaps.push_back(info);
    }

    return true;
}

const uint8_t* CBLPFile::GetMipMapData(uint32_t level) const {
    if (!m_valid || level >= m_mipMaps.size()) {
        return nullptr;
    }
    return m_fileData.data() + m_mipMaps[level].offset;
}

uint32_t CBLPFile::GetMipMapSize(uint32_t level) const {
    if (!m_valid || level >= m_mipMaps.size()) {
        return 0;
    }
    return m_mipMaps[level].size;
}

bool CBLPFile::DecodeToRGBA(std::vector<uint8_t> &output, uint32_t mipLevel) {
    if (!m_valid) {
        return false;
    }

    switch (m_header.format) {
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

bool CBLPFile::DecodePalette(std::vector<uint8_t> &output, uint32_t mipLevel) {
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

bool CBLPFile::DecodeDXT1(std::vector<uint8_t> &output, uint32_t mipLevel) {
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

    for (uint32_t y = 0; y < height; y += 4) {
        for (uint32_t x = 0; x < width; x += 4) {
            // Decode 4x4 block
            uint16_t color0 = *reinterpret_cast<const uint16_t*>(data);
            uint16_t color1 = *reinterpret_cast<const uint16_t*>(data + 2);
            uint32_t indices = *reinterpret_cast<const uint32_t*>(data + 4);
            data += 8;

            // Expand 16-bit colors to 32-bit
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
                        // 4-color mode
                        switch (idx) {
                            case 0: r = r0; g = g0; b = b0; a = 255; break;
                            case 1: r = r1; g = g1; b = b1; a = 255; break;
                            case 2: r = (2 * r0 + r1) / 3; g = (2 * g0 + g1) / 3; b = (2 * b0 + b1) / 3; a = 255; break;
                            case 3: r = (r0 + 2 * r1) / 3; g = (g0 + 2 * g1) / 3; b = (b0 + 2 * b1) / 3; a = 255; break;
                        }
                    } else {
                        // 3-color mode
                        switch (idx) {
                            case 0: r = r0; g = g0; b = b0; a = 255; break;
                            case 1: r = r1; g = g1; b = b1; a = 255; break;
                            case 2: r = (r0 + r1) / 2; g = (g0 + g1) / 2; b = (b0 + b1) / 2; a = 255; break;
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

bool CBLPFile::DecodeDXT3(std::vector<uint8_t> &output, uint32_t mipLevel) {
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

    for (uint32_t y = 0; y < height; y += 4) {
        for (uint32_t x = 0; x < width; x += 4) {
            // DXT3 has explicit alpha
            uint64_t alphaBlock = *reinterpret_cast<const uint64_t*>(data);
            data += 8;

            // Decode color block (same as DXT1)
            uint16_t color0 = *reinterpret_cast<const uint16_t*>(data);
            uint16_t color1 = *reinterpret_cast<const uint16_t*>(data + 2);
            uint32_t indices = *reinterpret_cast<const uint32_t*>(data + 4);
            data += 8;

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
                    uint8_t alpha = ((alphaBlock >> (alphaIdx * 4)) & 0xF) * 17;

                    uint8_t r, g, b;
                    switch (colorIdx) {
                        case 0: r = r0; g = g0; b = b0; break;
                        case 1: r = r1; g = g1; b = b1; break;
                        case 2: r = (2 * r0 + r1) / 3; g = (2 * g0 + g1) / 3; b = (2 * b0 + b1) / 3; break;
                        case 3: r = (r0 + 2 * r1) / 3; g = (g0 + 2 * g1) / 3; b = (b0 + 2 * b1) / 3; break;
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

bool CBLPFile::DecodeDXT5(std::vector<uint8_t> &output, uint32_t mipLevel) {
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

    for (uint32_t y = 0; y < height; y += 4) {
        for (uint32_t x = 0; x < width; x += 4) {
            // DXT5 alpha block
            uint8_t alpha0 = data[0];
            uint8_t alpha1 = data[1];
            uint64_t alphaBits = *reinterpret_cast<const uint16_t*>(data + 2) |
                                 (static_cast<uint64_t>(*reinterpret_cast<const uint16_t*>(data + 4)) << 16) |
                                 (static_cast<uint64_t>(*reinterpret_cast<const uint16_t*>(data + 6)) << 32);
            data += 8;

            // Color block (same as DXT1)
            uint16_t color0 = *reinterpret_cast<const uint16_t*>(data);
            uint16_t color1 = *reinterpret_cast<const uint16_t*>(data + 2);
            uint32_t indices = *reinterpret_cast<const uint32_t*>(data + 4);
            data += 8;

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

                    // Interpolate alpha
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
                        case 2: r = (2 * r0 + r1) / 3; g = (2 * g0 + g1) / 3; b = (2 * b0 + b1) / 3; break;
                        case 3: r = (r0 + 2 * r1) / 3; g = (g0 + 2 * g1) / 3; b = (b0 + 2 * b1) / 3; break;
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

bool CBLPFile::DecodeUncompressed(std::vector<uint8_t> &output, uint32_t mipLevel) {
    const uint8_t *data = GetMipMapData(mipLevel);
    uint32_t dataSize = GetMipMapSize(mipLevel);

    if (!data || dataSize == 0) {
        return false;
    }

    uint32_t width = m_header.width >> mipLevel;
    uint32_t height = m_header.height >> mipLevel;
    if (width == 0) width = 1;
    if (height == 0) height = 1;

    // Uncompressed BLP uses 32-bit BGRA
    output.resize(width * height * 4);

    for (uint32_t y = 0; y < height; ++y) {
        for (uint32_t x = 0; x < width; ++x) {
            uint32_t srcIdx = (y * width + x) * 4;
            uint32_t dstIdx = (y * width + x) * 4;

            if (srcIdx + 3 < dataSize) {
                // BGRA to RGBA
                output[dstIdx + 0] = data[srcIdx + 2];  // R
                output[dstIdx + 1] = data[srcIdx + 1];  // G
                output[dstIdx + 2] = data[srcIdx + 0];  // B
                output[dstIdx + 3] = data[srcIdx + 3];  // A
            }
        }
    }

    return true;
}

bool CBLPFile::DecodeJPEG(std::vector<uint8_t> &output, uint32_t mipLevel) {
    const uint8_t *data = GetMipMapData(mipLevel);
    uint32_t dataSize = GetMipMapSize(mipLevel);

    if (!data || dataSize == 0) {
        return false;
    }

    // BLP JPEG 格式特殊处理
    // BLP 文件中的 JPEG 数据需要先跳过前 4 个字节（标志位）
    // 然后才是标准的 JPEG 数据

    if (dataSize < 4) {
        return false;
    }

    // 跳过 BLP JPEG 头部标志
    const uint8_t *jpegData = data + 4;
    uint32_t jpegSize = dataSize - 4;

    // 验证 JPEG 标记 (SOI = 0xFFD8)
    if (jpegData[0] != 0xFF || jpegData[1] != 0xD8) {
        return false;
    }

    // 使用 jmemstorm 初始化内存管理
    jmemstorm_context ctx;
    jmemstorm_init(&ctx);

    // 获取纹理尺寸
    uint32_t width = m_header.width >> mipLevel;
    uint32_t height = m_header.height >> mipLevel;
    if (width == 0) width = 1;
    if (height == 0) height = 1;

    // 分配输出缓冲区
    output.resize(width * height * 4);

    // 注意：完整的 JPEG 解码需要集成完整的 IJG JPEG 库
    // 这里提供一个简化的实现，实际使用时需要：
    // 1. 初始化 JPEG 解码器
    // 2. 设置输入源
    // 3. 设置输出格式 (RGBA)
    // 4. 执行解码
    // 5. 清理资源

    // 由于完整的 IJG JPEG 库集成较为复杂，这里返回 false
    // 表示需要完整的 JPEG 解码器支持
    jmemstorm_cleanup(&ctx);

    return false;
}
