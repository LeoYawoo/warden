#pragma once

#include "CMessageFrame.h"
#include <cstdint>

// Reverse engineered from Warcraft III binary
// CSimpleMessageFrame is a simple message frame

class CSimpleMessageFrame : public CMessageFrame {
public:
    CSimpleMessageFrame();
    virtual ~CSimpleMessageFrame();

    // Message frame properties
    void SetTextColor(uint32_t color);
    uint32_t GetTextColor() const;

protected:
    uint32_t m_textColor;
};
