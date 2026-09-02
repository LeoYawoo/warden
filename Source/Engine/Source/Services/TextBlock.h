#pragma once

#include <cstdint>
#include <string>
#include <vector>

// Forward declarations
class CFont;

// Reverse engineered from Warcraft III binary
// TextBlock manages text block rendering

class TextBlock {
public:
    TextBlock();
    ~TextBlock();

    // Text operations
    void SetText(const char* text);
    const char* GetText() const;

    // Text properties
    float GetWidth() const;
    float GetHeight() const;
    void SetMaxWidth(float maxWidth);

    // Font operations
    void SetFont(CFont* font);
    CFont* GetFont() const;

    // Text alignment
    int32_t GetHJust() const;
    void SetHJust(int32_t just);
    int32_t GetVJust() const;
    void SetVJust(int32_t just);

    // Text operations
    void Update();

protected:
    std::string m_text;
    float m_maxWidth;
    CFont* m_font;
    int32_t m_hJust;
    int32_t m_vJust;
    float m_width;
    float m_height;
};
