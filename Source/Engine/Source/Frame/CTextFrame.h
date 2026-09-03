#pragma once

#include "CSimpleFrame.h"
#include <cstdint>
#include <string>

// Forward declarations
class CFont;

// Reverse engineered from Warcraft III binary
// CTextFrame is a text display frame

class CTextFrame : public CSimpleFrame {
public:
    CTextFrame();
    virtual ~CTextFrame();

    // TextFrame properties
    const char* GetText() const;
    void SetText(const char* text);

    // TextFrame font
    CFont* GetFont() const;
    void SetFont(CFont* font);

    // TextFrame alignment
    int32_t GetHJust() const;
    void SetHJust(int32_t just);

    int32_t GetVJust() const;
    void SetVJust(int32_t just);

    // TextFrame color
    uint32_t GetColor() const;
    void SetColor(uint32_t color);

protected:
    std::string m_text;
    CFont* m_font;
    int32_t m_hJust;
    int32_t m_vJust;
    uint32_t m_color;
};
