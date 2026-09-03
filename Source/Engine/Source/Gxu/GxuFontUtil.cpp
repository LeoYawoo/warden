#include "GxuFontUtil.h"
#include "GxuFont.h"
#include <cstring>

// Reverse engineered from Warcraft III binary

IGxuFont* GxuFontUtil::CreateFont(const char* fontName) {
    if (!fontName) return nullptr;
    GxuFont* font = new GxuFont();
    font->Load(fontName);
    return font;
}

void GxuFontUtil::DestroyFont(IGxuFont* font) {
    if (font) delete font;
}

float GxuFontUtil::GetStringWidth(IGxuFont* font, const char* str) {
    if (!font || !str) return 0.0f;
    float width = 0.0f;
    for (const char* p = str; *p; p++) {
        width += font->GetCharWidth(*p);
    }
    return width * font->GetScale();
}

float GxuFontUtil::GetStringHeight(IGxuFont* font, const char* str) {
    (void)str;
    if (!font) return 0.0f;
    return font->GetHeight() * font->GetScale();
}

int32_t GxuFontUtil::WrapText(IGxuFont* font, const char* text, float maxWidth, float* heights) {
    if (!font || !text || maxWidth <= 0) return 0;

    int32_t lineCount = 0;
    float currentLineWidth = 0.0f;
    float lineHeight = font->GetHeight() * font->GetScale();

    const char* p = text;
    while (*p) {
        if (*p == '\n') {
            // New line
            if (heights && lineCount < 100) {
                heights[lineCount] = lineHeight;
            }
            lineCount++;
            currentLineWidth = 0.0f;
            p++;
        } else {
            float charWidth = font->GetCharWidth(*p) * font->GetScale();
            if (currentLineWidth + charWidth > maxWidth) {
                // Wrap to new line
                if (heights && lineCount < 100) {
                    heights[lineCount] = lineHeight;
                }
                lineCount++;
                currentLineWidth = charWidth;
            } else {
                currentLineWidth += charWidth;
            }
            p++;
        }
    }

    // Add final line if there's remaining text
    if (currentLineWidth > 0) {
        if (heights && lineCount < 100) {
            heights[lineCount] = lineHeight;
        }
        lineCount++;
    }

    return lineCount;
}
