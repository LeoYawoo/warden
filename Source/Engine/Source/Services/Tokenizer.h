#pragma once

#include <cstdint>
#include <string>
#include <vector>

// Reverse engineered from Warcraft III binary
// Tokenizer manages string tokenization

class Tokenizer {
public:
    Tokenizer();
    ~Tokenizer();

    // Tokenizer operations
    void SetString(const char* str);
    const char* GetString() const;

    // Token operations
    bool NextToken(char* buffer, uint32_t bufferSize, const char* delimiters = " \t\n\r");
    bool PeekToken(char* buffer, uint32_t bufferSize, const char* delimiters = " \t\n\r") const;
    void Reset();

    // Token state
    bool HasMoreTokens() const;
    size_t GetPosition() const;

protected:
    std::string m_string;
    size_t m_position;
};
