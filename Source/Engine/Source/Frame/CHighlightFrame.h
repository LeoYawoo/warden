#pragma once

#include "CSimpleFrame.h"
#include <cstdint>

// Reverse engineered from Warcraft III binary
// CHighlightFrame is a highlighted frame

class CHighlightFrame : public CSimpleFrame {
public:
    CHighlightFrame();
    virtual ~CHighlightFrame();

    // Highlight properties
    bool IsHighlighted() const;
    void SetHighlighted(bool highlighted);

    uint32_t GetHighlightColor() const;
    void SetHighlightColor(uint32_t color);

protected:
    bool m_highlighted;
    uint32_t m_highlightColor;
};
