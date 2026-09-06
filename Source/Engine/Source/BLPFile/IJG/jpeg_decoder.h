#pragma once

// JPEG Decoder - Reference implementation based on IJG jpeglib architecture
// Decodes baseline DCT JPEG to RGBA pixel data

#include <cstdint>
#include <vector>
#include "jdmarker.h"

class JpegDecoder {
public:
    JpegDecoder();
    ~JpegDecoder();

    // Decode JPEG data to BGRA pixels
    // Input: raw JPEG data, optional known dimensions
    // Output: BGRA pixel data (width * height * 4 bytes)
    // Returns: true on success
    bool Decode(const uint8_t *data, size_t dataSize,
                std::vector<uint8_t> &output, uint32_t &width, uint32_t &height);

    // Set expected dimensions (used when SOF0 is missing)
    void SetDimensions(uint32_t w, uint32_t h) { m_explicitWidth = w; m_explicitHeight = h; }

private:
    // Bit reader
    struct BitReader {
        const uint8_t *data;
        size_t dataSize;
        size_t bytePos;
        uint8_t bitsLeft;
        uint8_t currentByte;

        void Init(const uint8_t *data, size_t size);
        uint32_t ReadBits(int nbits);
        uint32_t PeekBits(int nbits);
        void SkipBits(int nbits);
        bool EndOfData() const;
    };

    // Huffman table
    struct HuffTable {
        uint8_t  bits[17];    // Number of codes per bit length
        uint8_t  values[256]; // Symbol values
        int      minCode[17]; // Minimum code per bit length
        int      maxCode[17]; // Maximum code per bit length
        int      valOffset[17]; // Index into values for first symbol of each bit length
        bool     initialized;

        bool Build(const uint8_t *data);
        int Decode(BitReader &br) const;
    };

    // Component state
    struct Component {
        uint8_t id;
        uint8_t hSamp;
        uint8_t vSamp;
        uint8_t quantTable;
        uint8_t dcTable;
        uint8_t acTable;
        int16_t dcPred;
    };

    // Marker parsing
    bool ParseMarkers(const uint8_t *data, size_t size);
    bool ReadSOF(const uint8_t *data, size_t dataSize);
    bool ReadDQT(const uint8_t *data, size_t dataSize);
    bool ReadDHT(const uint8_t *data, size_t dataSize);
    bool ReadSOS(const uint8_t *data, size_t dataSize);

    // Entropy decoding
    int16_t DecodeDC(BitReader &br, int compIdx);
    int16_t DecodeAC(BitReader &br, int compIdx, int16_t block[64]);

    // IDCT
    void IDCT(int16_t block[64], int16_t *output);

    // Color conversion
    void YCbCrToBGRA(const int16_t *yBlock, const int16_t *cbBlock,
                      const int16_t *crBlock, uint8_t *out,
                      int blockX, int blockY, int imgWidth, int imgHeight,
                      int hSamp, int vSamp);

    // State
    JpegSOF m_sof;
    uint16_t m_restartInterval;
    int16_t m_quantTables[4][64];
    HuffTable m_dcTables[4];
    HuffTable m_acTables[4];
    Component m_components[4];
    uint8_t m_numComponents;

    // Scan data
    const uint8_t *m_scanData;
    size_t m_scanSize;

    // Explicit dimensions (from BLP header)
    uint32_t m_explicitWidth;
    uint32_t m_explicitHeight;
};
