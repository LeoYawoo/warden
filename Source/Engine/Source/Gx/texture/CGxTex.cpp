#include "CGxTex.h"

// TODO: Reverse engineer from IDA

CGxTex::CGxTex()
    : m_width(0)
    , m_height(0)
    , m_format(GxTex_Unknown)
    , m_locked(false)
    , m_flags()
    , m_needsUpdate(0)
    , m_updateRect()
    , m_needsFlagUpdate(0) {
}

CGxTex::CGxTex(EGxTexTarget /*target*/, uint32_t width, uint32_t height, uint32_t /*depth*/,
               EGxTexFormat format, EGxTexFormat /*dataFormat*/, CGxTexFlags flags,
               void * /*userArg*/, void (* /*userFunc*/)(EGxTexCommand, uint32_t, uint32_t, uint32_t, uint32_t, void *, uint32_t &, const void *&),
               const char * /*name*/)
    : m_width(width)
    , m_height(height)
    , m_format(format)
    , m_locked(false)
    , m_flags(flags)
    , m_needsUpdate(0)
    , m_updateRect()
    , m_needsFlagUpdate(0) {
}

CGxTex::~CGxTex() = default;

uint32_t CGxTex::GetWidth() const {
    return m_width;
}

uint32_t CGxTex::GetHeight() const {
    return m_height;
}

EGxTexFormat CGxTex::GetFormat() const {
    return m_format;
}

bool CGxTex::IsLocked() const {
    return m_locked;
}

void CGxTex::SetLocked(bool locked) {
    m_locked = locked;
}
