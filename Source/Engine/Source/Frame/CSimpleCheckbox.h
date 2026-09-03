#pragma once

#include "CCheckBox.h"
#include <cstdint>

// Reverse engineered from Warcraft III binary
// CSimpleCheckbox is a simple checkbox UI control

class CSimpleCheckbox : public CCheckBox {
public:
    CSimpleCheckbox();
    virtual ~CSimpleCheckbox();

    // Checkbox properties
    void SetTextColor(uint32_t color);
    uint32_t GetTextColor() const;

protected:
    uint32_t m_textColor;
};
