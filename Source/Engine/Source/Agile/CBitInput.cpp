#include "CBitInput.h"

// Reverse engineered from Warcraft III binary
// Address: 0x8490096 (InputBits)

CBitInput::CBitInput(const unsigned char* data, size_t size)
    : m_data(data), m_size(size), m_bitPosition(0), m_currentByte(0), m_bitsRemaining(0) {
}

CBitInput::~CBitInput() {
}

unsigned int CBitInput::InputBits(size_t count, size_t mask) {
    // Address: 0x8490096
    unsigned int result = 0;

    for (size_t i = 0; i < count; i++) {
        if (m_bitsRemaining == 0) {
            if (m_bitPosition >= m_size) {
                break;
            }
            m_currentByte = m_data[m_bitPosition++];
            m_bitsRemaining = 8;
        }

        result = (result << 1) | ((m_currentByte >> (m_bitsRemaining - 1)) & 1);
        m_bitsRemaining--;
    }

    return result & static_cast<unsigned int>(mask);
}

bool CBitInput::HasMoreBits() const {
    return m_bitPosition < m_size || m_bitsRemaining > 0;
}

size_t CBitInput::GetPosition() const {
    return m_bitPosition;
}

void CBitInput::Reset() {
    m_bitPosition = 0;
    m_currentByte = 0;
    m_bitsRemaining = 0;
}
