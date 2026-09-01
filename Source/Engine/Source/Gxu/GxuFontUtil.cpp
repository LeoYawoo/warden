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
    (void)font; (void)text; (void)maxWidth; (void)heights;
    // TODO: Implement text wrapping
    return 0;
}
