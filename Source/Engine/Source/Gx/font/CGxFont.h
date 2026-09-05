#pragma once

#include <cstdint>
#include <string>
#include "Common/TSLinkedNode.h"
#include "CGxString.h"

// Reverse engineered from Warcraft III binary
// CGxFont manages font resources

class CGxFont : public TSLinkedNode<CGxFont> {
public:
    CGxFont();
    ~CGxFont();

    // Font properties
    const char* GetName() const;
    const char* GetFontName() const;
    void SetFontName(const char* name);

    float GetSize() const;
    void SetSize(float size);

    float GetPixelSize() const;

    // Font state
    bool IsLoaded() const;
    void SetLoaded(bool loaded);

    int32_t Initialize(const char* name, int32_t a2, float fontHeight);

    // Glyph descriptor
    struct GlyphDesc {
        GLYPHBITMAPDATA bitmapData;
    };

    // Glyph operations
    GlyphDesc* NewCodeDesc(uint32_t code);
    float ComputeStep(uint32_t prevCode, uint32_t code);
    float ComputeStepFixedWidth(uint32_t prevCode, uint32_t code);
    float GetGlyphBearing(GlyphDesc* glyph, int32_t a2, float a3);

    // IDA reverse-engineered members
    uint32_t m_flags;

protected:
    std::string m_fontName;
    float m_size;
    bool m_loaded;
};
