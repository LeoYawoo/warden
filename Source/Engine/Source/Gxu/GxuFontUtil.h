#pragma once

#include <cstdint>

// Forward declarations
class IGxuFont;

// Reverse engineered from Warcraft III binary
// GxuFontUtil provides font utility functions

class GxuFontUtil {
public:
    // Font loading utilities
    static IGxuFont* CreateFont(const char* fontName);
    static void DestroyFont(IGxuFont* font);

    // Font metrics
    static float GetStringWidth(IGxuFont* font, const char* str);
    static float GetStringHeight(IGxuFont* font, const char* str);

    // Text wrapping
    static int32_t WrapText(IGxuFont* font, const char* text, float maxWidth, float* heights);
};
