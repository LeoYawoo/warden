#pragma once

#include <cstdint>
#include "../Types.h"
#include "Tempest/CiRect.h"

// Reverse engineered from Warcraft III binary
// CGxTex manages texture resources

using namespace Tempest;

// Texture flags structure
struct CGxTexFlags {
    uint8_t m_filter;
    uint8_t m_wrapU;
    uint8_t m_wrapV;
    uint8_t m_generateMipMaps;
    uint8_t m_anisotropic;
    uint8_t m_forceMipTracking;
    uint8_t m_renderTarget;
    uint8_t m_maxAnisotropy;

    CGxTexFlags() : m_filter(0), m_wrapU(0), m_wrapV(0), m_generateMipMaps(0), m_anisotropic(0), m_forceMipTracking(0), m_renderTarget(0), m_maxAnisotropy(0) {}
    CGxTexFlags(uint8_t filter, uint8_t wrapU, uint8_t wrapV, uint8_t genMips, uint8_t aniso, uint8_t forceMipTracking, uint8_t rt)
        : m_filter(filter), m_wrapU(wrapU), m_wrapV(wrapV), m_generateMipMaps(genMips), m_anisotropic(aniso), m_forceMipTracking(forceMipTracking), m_renderTarget(rt), m_maxAnisotropy(0) {}
};

// Texture creation parameters
struct CGxTexParms {
    EGxTexTarget target;
    uint32_t width;
    uint32_t height;
    uint32_t depth;
    EGxTexFormat format;
    EGxTexFormat dataFormat;
    CGxTexFlags flags;
    void *userArg;
    void (*userFunc)(EGxTexCommand, uint32_t, uint32_t, uint32_t, uint32_t, void *, uint32_t &, const void *&);
};

class CGxTex {
public:
    CGxTex();
    CGxTex(EGxTexTarget target, uint32_t width, uint32_t height, uint32_t depth,
           EGxTexFormat format, EGxTexFormat dataFormat, CGxTexFlags flags,
           void *userArg, void (*userFunc)(EGxTexCommand, uint32_t, uint32_t, uint32_t, uint32_t, void *, uint32_t &, const void *&),
           const char *name);
    ~CGxTex();

    // Texture properties
    uint32_t GetWidth() const;
    uint32_t GetHeight() const;
    EGxTexFormat GetFormat() const;

    // Texture state
    bool IsLocked() const;
    void SetLocked(bool locked);

    // IDA reverse-engineered members
    uint32_t m_width;
    uint32_t m_height;
    EGxTexFormat m_format;
    bool m_locked;
    CGxTexFlags m_flags;
    int32_t m_needsUpdate;
    CiRect m_updateRect;
    int32_t m_needsFlagUpdate;
};
