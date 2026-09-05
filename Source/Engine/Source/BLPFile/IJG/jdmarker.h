#pragma once

// JPEG marker definitions
// Reference: IJG jpeglib - jdmarker.h

constexpr uint8_t M_SOF0  = 0xC0;  // Start Of Frame (baseline DCT)
constexpr uint8_t M_SOF1  = 0xC1;  // Start Of Frame (extended sequential DCT)
constexpr uint8_t M_SOF2  = 0xC2;  // Start Of Frame (progressive DCT)
constexpr uint8_t M_DHT   = 0xC4;  // Define Huffman Table
constexpr uint8_t M_SOS   = 0xDA;  // Start Of Scan
constexpr uint8_t M_DQT   = 0xDB;  // Define Quantization Table
constexpr uint8_t M_DRI   = 0xDD;  // Define Restart Interval
constexpr uint8_t M_APP0  = 0xE0;  // Application segment 0 (JFIF)
constexpr uint8_t M_APP1  = 0xE1;  // Application segment 1 (EXIF)
constexpr uint8_t M_COM   = 0xFE;  // Comment
constexpr uint8_t M_EOI   = 0xD9;  // End Of Image
constexpr uint8_t M_RST0  = 0xD0;  // Restart 0
constexpr uint8_t M_RST7  = 0xD7;  // Restart 7
constexpr uint8_t M_DAC   = 0xCC;  // Define Arithmetic Coding

// SOF marker data
struct JpegSOF {
    uint8_t  precision;      // Sample precision (usually 8)
    uint16_t height;         // Image height
    uint16_t width;          // Image width
    uint8_t  numComponents;  // Number of components
    struct {
        uint8_t id;          // Component identifier
        uint8_t hSamp;       // Horizontal sampling factor
        uint8_t vSamp;       // Vertical sampling factor
        uint8_t quantTable;  // Quantization table selector
    } components[4];
};
