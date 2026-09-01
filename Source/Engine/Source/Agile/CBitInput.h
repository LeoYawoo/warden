#pragma once

#include "Common/TRefCnt.h"

// Reverse engineered from Warcraft III binary
// CBitInput reads bits from a byte stream

class CBitInput {
public:
    CBitInput(const unsigned char* data, size_t size);
    ~CBitInput();

    // Read bits from the stream
    unsigned int InputBits(size_t count, size_t mask);

    // Check if there are more bits
    bool HasMoreBits() const;

    // Get current position
    size_t GetPosition() const;

    // Reset to beginning
    void Reset();

private:
    const unsigned char* m_data;
    size_t m_size;
    size_t m_bitPosition;
    unsigned int m_currentByte;
    int m_bitsRemaining;
};
