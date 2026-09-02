#include "Tokenizer.h"
#include <cstring>

// Reverse engineered from Warcraft III binary

Tokenizer::Tokenizer() : m_position(0) {}
Tokenizer::~Tokenizer() {}

void Tokenizer::SetString(const char* str) {
    if (str) {
        m_string = str;
    } else {
        m_string.clear();
    }
    m_position = 0;
}

const char* Tokenizer::GetString() const {
    return m_string.c_str();
}

bool Tokenizer::NextToken(char* buffer, uint32_t bufferSize, const char* delimiters) {
    if (!buffer || bufferSize == 0 || m_position >= m_string.size()) {
        return false;
    }

    // Skip leading delimiters
    while (m_position < m_string.size() && strchr(delimiters, m_string[m_position])) {
        m_position++;
    }

    if (m_position >= m_string.size()) {
        return false;
    }

    // Find token end
    size_t start = m_position;
    while (m_position < m_string.size() && !strchr(delimiters, m_string[m_position])) {
        m_position++;
    }

    // Copy token
    size_t length = m_position - start;
    if (length >= bufferSize) {
        length = bufferSize - 1;
    }

    memcpy(buffer, &m_string[start], length);
    buffer[length] = '\0';

    return true;
}

bool Tokenizer::PeekToken(char* buffer, uint32_t bufferSize, const char* delimiters) const {
    Tokenizer temp = *this;
    return temp.NextToken(buffer, bufferSize, delimiters);
}

void Tokenizer::Reset() {
    m_position = 0;
}

bool Tokenizer::HasMoreTokens() const {
    size_t pos = m_position;
    while (pos < m_string.size() && strchr(" \t\n\r", m_string[pos])) {
        pos++;
    }
    return pos < m_string.size();
}

size_t Tokenizer::GetPosition() const {
    return m_position;
}
