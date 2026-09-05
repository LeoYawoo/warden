#include "CTexture.h"

// TODO: Reverse engineer from IDA

// Static member variable definitions
uint32_t CTexture::s_filterMode = 0;
uint32_t CTexture::s_maxAnisotropy = 1;

CTexture::CTexture()
    : m_linktofull()
    , m_linktoslot()
    , m_hashval(0)
    , m_key()
    , gxWidth(0)
    , gxHeight(0)
    , flags(0)
    , asyncObject(nullptr)
    , loadStatus()
    , atlas(0)
    , gxTex(nullptr)
    , filename(nullptr)
    , dataFormat(GxTex_Unknown)
    , gxTexFormat(GxTex_Unknown)
    , gxTexTarget(GxTex_2d)
    , gxTexFlags()
    , alphaBits(0)
    , bestMip(0)
    , m_maxAnisotropy(1) {
}

CTexture::~CTexture() = default;

uint32_t CTexture::GetWidth() const {
    return gxWidth;
}

uint32_t CTexture::GetHeight() const {
    return gxHeight;
}

EGxTexFormat CTexture::GetFormat() const {
    return gxTexFormat;
}

bool CTexture::IsLoaded() const {
    return gxTex != nullptr;
}

void CTexture::SetLoaded(bool /*loaded*/) {
    // TODO: Reverse engineer from IDA
}
