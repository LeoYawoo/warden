// JPEG Decoder - Reference implementation based on IJG jpeglib architecture
// Implements baseline DCT JPEG decoding to BGRA pixel output

#include "jpeg_decoder.h"
#include <cstring>
#include <cmath>
#include <algorithm>
#include <cstdio>

// ============================================================
// Zigzag scan order (standard JPEG)
// ============================================================
static const int ZIGZAG[64] = {
     0,  1,  8, 16,  9,  2,  3, 10,
    17, 24, 32, 25, 18, 11,  4,  5,
    12, 19, 26, 33, 40, 48, 41, 34,
    27, 20, 13,  6,  7, 14, 21, 28,
    35, 42, 49, 56, 57, 50, 43, 36,
    29, 22, 15, 23, 30, 37, 44, 51,
    58, 59, 52, 45, 38, 31, 39, 46,
    53, 60, 61, 54, 47, 55, 62, 63
};

// ============================================================
// BitReader
// ============================================================
void JpegDecoder::BitReader::Init(const uint8_t *d, size_t size) {
    data = d;
    dataSize = size;
    bytePos = 0;
    bitsLeft = 0;
    currentByte = 0;
}

uint32_t JpegDecoder::BitReader::ReadBits(int nbits) {
    uint32_t val = 0;
    while (nbits > 0) {
        if (bitsLeft == 0) {
            if (bytePos >= dataSize) return 0;
            currentByte = data[bytePos++];
            if (currentByte == 0xFF) {
                // Skip stuffing byte
                if (bytePos < dataSize && data[bytePos] == 0x00) {
                    bytePos++;
                }
            }
            bitsLeft = 8;
        }
        int take = std::min(nbits, (int)bitsLeft);
        val = (val << take) | ((currentByte >> (bitsLeft - take)) & ((1 << take) - 1));
        bitsLeft -= take;
        nbits -= take;
    }
    return val;
}

uint32_t JpegDecoder::BitReader::PeekBits(int nbits) {
    uint32_t saved = 0;
    uint32_t val = 0;
    int tempBits = bitsLeft;
    size_t tempPos = bytePos;
    uint8_t tempByte = currentByte;

    while (nbits > 0) {
        if (tempBits == 0) {
            if (tempPos >= dataSize) break;
            tempByte = data[tempPos++];
            if (tempByte == 0xFF && tempPos < dataSize && data[tempPos] == 0x00) {
                tempPos++;
            }
            tempBits = 8;
        }
        int take = std::min(nbits, (int)tempBits);
        val = (val << take) | ((tempByte >> (tempBits - take)) & ((1 << take) - 1));
        tempBits -= take;
        nbits -= take;
    }
    return val;
}

void JpegDecoder::BitReader::SkipBits(int nbits) {
    while (nbits > 0) {
        if (bitsLeft == 0) {
            if (bytePos >= dataSize) return;
            currentByte = data[bytePos++];
            if (currentByte == 0xFF) {
                if (bytePos < dataSize && data[bytePos] == 0x00) {
                    bytePos++;
                }
            }
            bitsLeft = 8;
        }
        int take = std::min(nbits, (int)bitsLeft);
        bitsLeft -= take;
        nbits -= take;
    }
}

bool JpegDecoder::BitReader::EndOfData() const {
    return bytePos >= dataSize;
}

// ============================================================
// Huffman table
// ============================================================
bool JpegDecoder::HuffTable::Build(const uint8_t *data) {
    std::memset(bits, 0, sizeof(bits));
    std::memset(values, 0, sizeof(values));
    std::memset(maxCode, 0, sizeof(maxCode));
    std::memset(valOffset, 0, sizeof(valOffset));
    initialized = false;

    // Count symbols per bit length
    int totalSymbols = 0;
    for (int i = 1; i <= 16; i++) {
        bits[i] = data[i - 1];
        totalSymbols += bits[i];
    }

    if (totalSymbols > 256) return false;

    // Copy symbol values
    std::memcpy(values, data + 16, totalSymbols);

    // Compute maximum code for each bit length
    int code = 0;
    int si = 0;
    for (int i = 1; i <= 16; i++) {
        code += bits[i];
        maxCode[i] = code - 1;
        valOffset[i] = si;
        si += bits[i];
        code <<= 1;
    }

    initialized = true;
    return true;
}

int JpegDecoder::HuffTable::Decode(BitReader &br) const {
    if (!initialized) return 0;

    // IJG approach: read 8 bits first, then extend bit by bit
    int l = 8;
    int code = br.ReadBits(l);

    while (code > maxCode[l]) {
        code = (code << 1) | br.ReadBits(1);
        l++;
    }

    if (l > 16) return 0;

    return values[valOffset[l] + (code - (maxCode[l] - (1 << l) + 1))];
}

// ============================================================
// IDCT (Inverse Discrete Cosine Transform)
// ============================================================
void JpegDecoder::IDCT(int16_t block[64], int16_t *output) {
    // Standard JPEG IDCT using 1D row/column decomposition
    // Based on IJG jidctint.c approach

    int tmp[64];

    // First pass: IDCT on columns
    for (int col = 0; col < 8; col++) {
        for (int row = 0; row < 8; row++) {
            float sum = 0.0f;
            for (int u = 0; u < 8; u++) {
                float cu = (u == 0) ? (1.0f / std::sqrt(2.0f)) : 1.0f;
                sum += cu * block[u * 8 + col] * std::cos((2.0f * row + 1.0f) * u * 3.14159265f / 16.0f);
            }
            tmp[row * 8 + col] = (int)std::round(sum / 2.0f);
        }
    }

    // Second pass: IDCT on rows
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            float sum = 0.0f;
            for (int v = 0; v < 8; v++) {
                float cv = (v == 0) ? (1.0f / std::sqrt(2.0f)) : 1.0f;
                sum += cv * tmp[row * 8 + v] * std::cos((2.0f * col + 1.0f) * v * 3.14159265f / 16.0f);
            }
            int val = (int)std::round(sum / 2.0f) + 128;
            output[row * 8 + col] = static_cast<int16_t>(std::max(0, std::min(255, val)));
        }
    }
}

// ============================================================
// Marker parsing
// ============================================================
bool JpegDecoder::ParseMarkers(const uint8_t *data, size_t size) {
    size_t pos = 0;
    bool foundSOF = false;
    bool foundSOS = false;

    while (pos < size - 1) {
        if (data[pos] != 0xFF) { pos++; continue; }

        uint8_t marker = data[pos + 1];
        if (pos >= 131 && pos <= 135) {
        }
        if (pos >= 620 && pos <= 624) {
        }
        pos += 2;

        // SOI and EOI have no length field
        if (marker == 0xD8) continue; // SOI
        if (marker == 0x00 || marker == 0xFF) continue; // Stuffing/padding
        if (marker == M_EOI) break;
        if (marker >= M_RST0 && marker <= M_RST7) continue; // RST markers

        // Read marker length
        if (pos + 1 >= size) break;
        uint16_t length = (data[pos] << 8) | data[pos + 1];
        pos += 2;

        if (marker == M_SOF0 || marker == M_SOF1 || marker == M_SOF2) {
            if (length >= 8 && ReadSOF(data + pos - 2, length)) {
                foundSOF = true;
            }
            pos += length - 2;
        } else if (marker == M_DQT) {
            if (!ReadDQT(data + pos, length - 2)) return false;
            pos += length - 2; // Skip past DQT data
        } else if (marker == M_DHT) {
            if (!ReadDHT(data + pos, length - 2)) return false;
            pos += length - 2; // Skip past DHT data
        } else if (marker == M_SOS) {
            // If SOF0 not found, setup default components before reading SOS
            if (!foundSOF) {
                m_sof.numComponents = 3;
                m_sof.components[0] = {1, 1, 1, 0};
                m_sof.components[1] = {2, 1, 1, 1};
                m_sof.components[2] = {3, 1, 1, 1};
                foundSOF = true;
            }
            if (!ReadSOS(data + pos, length - 2)) return false;
            // Save scan data position - everything after SOS is entropy data
            m_scanData = data + pos + length;
            m_scanSize = size - (pos + length);
            foundSOS = true;
            break; // Stop parsing markers - rest is entropy data
        } else if (marker == M_DRI) {
            m_restartInterval = (data[pos] << 8) | data[pos + 1];
        }
    }

    // If SOF0 not found, create default 3-component setup
    if (!foundSOF && foundSOS) {
        m_sof.numComponents = 3;
        m_sof.components[0] = {1, 1, 1, 0};
        m_sof.components[1] = {2, 1, 1, 1};
        m_sof.components[2] = {3, 1, 1, 1};
        foundSOF = true;
    }

    return foundSOF && foundSOS;
}

bool JpegDecoder::ReadSOF(const uint8_t *data, size_t dataSize) {
    if (dataSize < 15) return false;

    m_sof.precision = data[2];
    m_sof.height = (data[3] << 8) | data[4];
    m_sof.width = (data[5] << 8) | data[6];
    m_sof.numComponents = data[7];

    if (m_sof.numComponents > 4) return false;

    for (int i = 0; i < m_sof.numComponents; i++) {
        size_t off = 8 + i * 3;
        m_sof.components[i].id = data[off];
        m_sof.components[i].hSamp = (data[off + 1] >> 4) & 0xF;
        m_sof.components[i].vSamp = data[off + 1] & 0xF;
        m_sof.components[i].quantTable = data[off + 2];
    }

    return true;
}

bool JpegDecoder::ReadDQT(const uint8_t *data, size_t dataSize) {
    size_t pos = 0;
    while (pos < dataSize) {
        uint8_t info = data[pos++];
        int tableIdx = info & 0x0F;
        int precision = (info >> 4) & 0x0F;

        if (tableIdx > 3) return false;

        for (int i = 0; i < 64; i++) {
            if (precision == 0) {
                m_quantTables[tableIdx][ZIGZAG[i]] = data[pos++];
            } else {
                m_quantTables[tableIdx][ZIGZAG[i]] = (data[pos] << 8) | data[pos + 1];
                pos += 2;
            }
        }
    }
    return true;
}

bool JpegDecoder::ReadDHT(const uint8_t *data, size_t dataSize) {
    size_t pos = 0;
    while (pos < dataSize) {
        uint8_t info = data[pos++];
        int tableIdx = info & 0x0F;
        int isAC = (info >> 4) & 0x01;

        if (tableIdx > 3) return false;

        HuffTable &table = isAC ? m_acTables[tableIdx] : m_dcTables[tableIdx];
        if (!table.Build(data + pos)) return false;

        int totalSymbols = 0;
        for (int i = 1; i <= 16; i++) totalSymbols += table.bits[i];
        pos += 16 + totalSymbols;
    }
    return true;
}

bool JpegDecoder::ReadSOS(const uint8_t *data, size_t dataSize) {
    if (dataSize < 6) {
        return false;
    }

    uint8_t numComp = data[0];
    m_numComponents = numComp;

    for (int i = 0; i < numComp; i++) {
        size_t off = 1 + i * 2;
        uint8_t compId = data[off];
        uint8_t tables = data[off + 1];

        // Find component by ID
        for (int j = 0; j < m_sof.numComponents; j++) {
            if (m_sof.components[j].id == compId) {
                m_components[j].id = compId;
                m_components[j].hSamp = m_sof.components[j].hSamp;
                m_components[j].vSamp = m_sof.components[j].vSamp;
                m_components[j].quantTable = m_sof.components[j].quantTable;
                m_components[j].dcTable = (tables >> 4) & 0x0F;
                m_components[j].acTable = tables & 0x0F;
                m_components[j].dcPred = 0;
                break;
            }
        }
    }

    return true;
}

// ============================================================
// Entropy decoding
// ============================================================
int16_t JpegDecoder::DecodeDC(BitReader &br, int compIdx) {
    int tableIdx = m_components[compIdx].dcTable;
    int symbol = m_dcTables[tableIdx].Decode(br);

    int diff = 0;
    if (symbol != 0) {
        diff = br.ReadBits(symbol);
        if (diff < (1 << (symbol - 1))) {
            diff -= (1 << symbol) - 1;
        }
    }

    m_components[compIdx].dcPred += diff;
    return m_components[compIdx].dcPred;
}

int16_t JpegDecoder::DecodeAC(BitReader &br, int compIdx, int16_t block[64]) {
    int tableIdx = m_components[compIdx].acTable;
    std::memset(block, 0, 64 * sizeof(int16_t));

    int k = 1;
    while (k < 64) {
        int symbol = m_acTables[tableIdx].Decode(br);

        if (symbol == 0x00) {
            // EOB - rest of block is zero
            break;
        }

        int runLength = (symbol >> 4) & 0x0F;
        int size = symbol & 0x0F;

        if (symbol == 0xF0) {
            // ZRL - skip 16 zeros
            k += 16;
            continue;
        }

        k += runLength;
        if (k >= 64) break;

        int val = br.ReadBits(size);
        if (val < (1 << (size - 1))) {
            val -= (1 << size) - 1;
        }

        block[ZIGZAG[k]] = val;
        k++;
    }

    return 0;
}

// ============================================================
// Main decode function
// ============================================================
JpegDecoder::JpegDecoder()
    : m_restartInterval(0), m_numComponents(0),
      m_scanData(nullptr), m_scanSize(0),
      m_explicitWidth(0), m_explicitHeight(0) {
    std::memset(&m_sof, 0, sizeof(m_sof));
    std::memset(m_quantTables, 0, sizeof(m_quantTables));
    std::memset(m_components, 0, sizeof(m_components));
}

JpegDecoder::~JpegDecoder() = default;

bool JpegDecoder::Decode(const uint8_t *data, size_t dataSize,
                         std::vector<uint8_t> &output, uint32_t &width, uint32_t &height) {
    if (!data || dataSize < 2) return false;

    // Validate JPEG SOI marker
    if (data[0] != 0xFF || data[1] != 0xD8) {
        return false;
    }

    // Parse markers
    if (!ParseMarkers(data, dataSize)) {
        return false;
    }

            m_sof.width, m_sof.height, m_numComponents, (void*)m_scanData, m_scanSize);

    width = m_sof.width ? m_sof.width : m_explicitWidth;
    height = m_sof.height ? m_sof.height : m_explicitHeight;

    if (width == 0 || height == 0 || m_numComponents == 0) {
        return false;
    }

    // Allocate output (BGRA)
    output.resize(width * height * 4);

    // Allocate working buffers for MCU blocks
    int mcuWidth = 8 * m_components[0].hSamp;
    int mcuHeight = 8 * m_components[0].vSamp;
    int mcusX = (width + mcuWidth - 1) / mcuWidth;
    int mcusY = (height + mcuHeight - 1) / mcuHeight;

    std::vector<int16_t> blockBuffer(64);

    // Allocate component buffers
    std::vector<int16_t> yBuffer(mcuWidth * mcuHeight * mcusX * mcusY);
    std::vector<int16_t> cbBuffer(mcuWidth * mcuHeight * mcusX * mcusY);
    std::vector<int16_t> crBuffer(mcuWidth * mcuHeight * mcusX * mcusY);

    BitReader br;
    br.Init(m_scanData, m_scanSize);

    // Reset DC predictors
    for (int i = 0; i < m_numComponents; i++) {
        m_components[i].dcPred = 0;
    }

    // Decode MCUs
    int restartCount = 0;
    for (int mcy = 0; mcy < mcusY; mcy++) {
        for (int mcx = 0; mcx < mcusX; mcx++) {
            // Check for restart marker
            if (m_restartInterval > 0) {
                restartCount++;
                if (restartCount >= m_restartInterval) {
                    restartCount = 0;
                    // Align to byte boundary and skip restart marker
                    if (br.bitsLeft > 0) {
                        br.SkipBits(br.bitsLeft);
                    }
                    br.SkipBits(8); // Skip marker byte
                    br.SkipBits(8); // Skip marker code

                    for (int i = 0; i < m_numComponents; i++) {
                        m_components[i].dcPred = 0;
                    }
                }
            }

            // Decode each component's MCU
            for (int comp = 0; comp < m_numComponents; comp++) {
                int hSamp = m_components[comp].hSamp;
                int vSamp = m_components[comp].vSamp;

                for (int vy = 0; vy < vSamp; vy++) {
                    for (int vx = 0; vx < hSamp; vx++) {
                        // Decode DC coefficient
                        int16_t dc = DecodeDC(br, comp);

                        // Decode AC coefficients
                        int16_t acBlock[64] = {};
                        DecodeAC(br, comp, acBlock);

                        // Combine DC + AC
                        blockBuffer[0] = dc;
                        for (int i = 1; i < 64; i++) {
                            blockBuffer[i] = acBlock[i];
                        }

                        // Dequantize
                        int quantIdx = m_components[comp].quantTable;
                        for (int i = 0; i < 64; i++) {
                            blockBuffer[i] *= m_quantTables[quantIdx][i];
                        }

                        // IDCT
                        int16_t spatial[64];
                        IDCT(blockBuffer.data(), spatial);

                        // Place in component buffer
                        int compWidth = mcusX * 8;
                        for (int sy = 0; sy < 8; sy++) {
                            for (int sx = 0; sx < 8; sx++) {
                                int bx = mcx * mcuWidth + vx * 8 + sx;
                                int by = mcy * mcuHeight + vy * 8 + sy;
                                if (bx < width && by < height) {
                                    int idx = by * width + bx;
                                    if (comp == 0) yBuffer[idx] = spatial[sy * 8 + sx];
                                    else if (comp == 1) cbBuffer[idx] = spatial[sy * 8 + sx];
                                    else if (comp == 2) crBuffer[idx] = spatial[sy * 8 + sx];
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // BLP1 JPEG: components are raw BGRA, not YCbCr
    // No color transform needed - IDCT output is used directly as pixel values
    // Component order: comp0=B, comp1=G, comp2=R (swap B↔R for standard output)
    for (int y = 0; y < (int)height; y++) {
        for (int x = 0; x < (int)width; x++) {
            int idx = (y * width + x) * 4;
            int comp0 = yBuffer[y * width + x] + 128;  // B channel
            int comp1 = cbBuffer[y * width + x] + 128;  // G channel
            int comp2 = crBuffer[y * width + x] + 128;  // R channel

            output[idx + 0] = static_cast<uint8_t>(std::max(0, std::min(255, comp2))); // R
            output[idx + 1] = static_cast<uint8_t>(std::max(0, std::min(255, comp1))); // G
            output[idx + 2] = static_cast<uint8_t>(std::max(0, std::min(255, comp0))); // B
            output[idx + 3] = 255; // A
        }
    }

    return true;
}
