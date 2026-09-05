#include "CGxFont.h"

// TODO: Reverse engineer from IDA

CGxFont::CGxFont()
    : m_flags(0)
    , m_fontName()
    , m_size(0.0f)
    , m_loaded(false) {
}

CGxFont::~CGxFont() = default;

const char *CGxFont::GetName() const {
    return m_fontName.c_str();
}

float CGxFont::GetPixelSize() const {
    return m_size;
}

int32_t CGxFont::Initialize(const char * /*name*/, int32_t /*flags*/, float /*fontHeight*/) {
    // TODO: Reverse engineer from IDA
    return 0;
}

CGxFont::GlyphDesc *CGxFont::NewCodeDesc(uint32_t /*code*/) {
    // TODO: Reverse engineer from IDA
    return nullptr;
}

float CGxFont::ComputeStep(uint32_t /*prevCode*/, uint32_t /*code*/) {
    // TODO: Reverse engineer from IDA
    return 0.0f;
}

float CGxFont::ComputeStepFixedWidth(uint32_t /*prevCode*/, uint32_t /*code*/) {
    // TODO: Reverse engineer from IDA
    return 0.0f;
}

float CGxFont::GetGlyphBearing(GlyphDesc * /*glyph*/, int32_t /*a2*/, float /*a3*/) {
    // TODO: Reverse engineer from IDA
    return 0.0f;
}
