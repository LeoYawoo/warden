#pragma once

#include "CButtonFrame.h"
#include <cstdint>
#include <string>

// Reverse engineered from Warcraft III binary
// CTextButtonFrame is a button with text

class CTextButtonFrame : public CButtonFrame {
public:
    CTextButtonFrame();
    virtual ~CTextButtonFrame();

    // TextButton properties
    uint32_t GetTextColor() const;
    void SetTextColor(uint32_t color);

    uint32_t GetDisabledColor() const;
    void SetDisabledColor(uint32_t color);

protected:
    uint32_t m_textColor;
    uint32_t m_disabledColor;
};
