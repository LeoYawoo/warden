#pragma once

#include <cstdint>
#include <string>
#include "../Types.h"
#include "Agile/CStatus.h"
#include "Agile/CHandleObject.h"
#include "Common/TSLink.h"
#include "CGxTex.h"
#include "CBLPFile.h"
#include "StormMac/CAsyncObject.h"

// Forward declarations
class CGxTex;
class CAsyncObject;

// Reverse engineered from Warcraft III binary
// CTexture manages texture resources

class CTexture : public CHandleObject {
public:
    CTexture();
    ~CTexture();

    // Texture properties
    uint32_t GetWidth() const;
    uint32_t GetHeight() const;
    EGxTexFormat GetFormat() const;

    // Texture state
    bool IsLoaded() const;
    void SetLoaded(bool loaded);

    // Hash table link members (used by TSHashTable)
    TSLink<CTexture> m_linktofull;
    TSLink<CTexture> m_linktoslot;
    uint32_t m_hashval;
    HASHKEY_TEXTUREFILE m_key;

    // Static filter state
    static uint32_t s_filterMode;
    static uint32_t s_maxAnisotropy;

    // IDA reverse-engineered members
    uint32_t gxWidth;
    uint32_t gxHeight;
    uint32_t flags;
    CAsyncObject* asyncObject;
    CStatus loadStatus;
    int32_t atlas;
    CGxTex* gxTex;
    char* filename;
    EGxTexFormat dataFormat;
    EGxTexFormat gxTexFormat;
    EGxTexTarget gxTexTarget;
    CGxTexFlags gxTexFlags;
    uint32_t alphaBits;
    uint32_t bestMip;
    uint32_t m_maxAnisotropy;
};
