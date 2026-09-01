#pragma once

#include <cstdint>

// Reverse engineered from Warcraft III binary
// IGxuFontGlyph is the interface for font glyph rendering

class IGxuFontGlyph {
public:
    virtual ~IGxuFontGlyph() = default;

    // Glyph properties
    virtual uint32_t GetGlyphId() const = 0;
    virtual float GetWidth() const = 0;
    virtual float GetHeight() const = 0;

    // Glyph UV coordinates
    virtual float GetU0() const = 0;
    virtual float GetV0() const = 0;
    virtual float GetU1() const = 0;
    virtual float GetV1() const = 0;

    // Glyph offset
    virtual float GetOffsetX() const = 0;
    virtual float GetOffsetY() const = 0;

protected:
    uint32_t m_glyphId;
    float m_width;
    float m_height;
    float m_u0;
    float m_v0;
    float m_u1;
    float m_v1;
    float m_offsetX;
    float m_offsetY;
};
