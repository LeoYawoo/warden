#pragma once

#include "CButtonFrame.h"
#include <cstdint>
#include <string>

// Forward declarations
class CGxuFont;

// Reverse engineered from Warcraft III binary
// CSimpleButton is a simple button UI control

class CSimpleButton : public CButtonFrame {
public:
    CSimpleButton();
    virtual ~CSimpleButton();

    // Button properties
    void SetTextColor(uint32_t color);
    uint32_t GetTextColor() const;

    void SetFont(CGxuFont* font);
    CGxuFont* GetFont() const;

    // Button state
    bool IsDisabled() const;
    void SetDisabled(bool disabled);

protected:
    uint32_t m_textColor;
    CGxuFont* m_font;
    bool m_disabled;
};
