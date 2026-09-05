#pragma once

#include <cstdint>
#include "Common/TSLinkedNode.h"
#include "Tempest/C2Vector.h"
#include "Tempest/C3Vector.h"
#include "Tempest/CImVector.h"
#include "../Types.h"

class CGxFont;

// Reverse engineered from Warcraft III binary
// CGxString manages a rendered text string

struct GLYPHBITMAPDATA {
    void* m_data;
    uint32_t m_dataSize;
    int32_t m_glyphPitch;
    uint32_t m_glyphWidth;
    uint32_t m_glyphHeight;
    uint32_t m_glyphCellWidth;
    double m_glyphAdvance;
    double m_glyphBearing;
    int32_t m_yOffset;
    int32_t m_yStart;
};

class CGxString : public TSLinkedNode<CGxString> {
public:
    CGxString();
    ~CGxString();

    static CGxString* GetNewString(int32_t a1);

    int32_t Initialize(float fontHeight, const Tempest::C3Vector& position,
                    float blockWidth, float blockHeight, CGxFont* font, const char* text,
                    EGxFontVJusts vJust, EGxFontHJusts hJust, float spacing,
                    uint32_t flags, const Tempest::CImVector& color, float scale);

    void AddShadow(Tempest::C2Vector offset, const Tempest::CImVector& color);
    void SetColor(const Tempest::CImVector& color);
    void SetStringPosition(const Tempest::C3Vector& position);
    void Tick();
    void Recycle();

    // IDA reverse-engineered members
    uint32_t m_flags;
};
