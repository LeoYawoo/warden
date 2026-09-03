#pragma once

#include "CSimpleFrame.h"
#include <cstdint>

// Reverse engineered from Warcraft III binary
// CSimpleStatusBar is a simple status bar

class CSimpleStatusBar : public CSimpleFrame {
public:
    CSimpleStatusBar();
    virtual ~CSimpleStatusBar();

    // StatusBar properties
    float GetProgress() const;
    void SetProgress(float progress);

    uint32_t GetBarColor() const;
    void SetBarColor(uint32_t color);

    uint32_t GetBackgroundColor() const;
    void SetBackgroundColor(uint32_t color);

protected:
    float m_progress;
    uint32_t m_barColor;
    uint32_t m_backgroundColor;
};
