#pragma once

#include "CFrame.h"
#include <cstdint>

// Reverse engineered from Warcraft III binary
// CScreenFrame is a screen-sized frame

class CScreenFrame : public CFrame {
public:
    CScreenFrame();
    virtual ~CScreenFrame();

    // ScreenFrame properties
    int32_t GetScreenWidth() const;
    int32_t GetScreenHeight() const;

    // ScreenFrame operations
    void SetScreenSize(int32_t width, int32_t height);

protected:
    int32_t m_screenWidth;
    int32_t m_screenHeight;
};
