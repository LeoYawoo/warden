#pragma once

#include <cstdint>
#include "Common/TSLink.h"

// Reverse engineered from Warcraft III binary
// CGxBuf manages graphics buffer resources

class CGxPool;

class CGxBuf {
public:
    CGxBuf();
    CGxBuf(CGxPool* pool, uint32_t itemSize, uint32_t itemCount, uint32_t index);
    ~CGxBuf();

    // Buffer properties
    uint32_t GetSize() const;
    void SetSize(uint32_t size);

    uint32_t GetOffset() const;
    void SetOffset(uint32_t offset);

    bool IsLocked() const;
    void SetLocked(bool locked);

    // Hash table link member (used by TSExplicitList in CGxPool)
    TSLink<CGxBuf> m_linktofull;

    // Member variables
    uint32_t m_itemSize;
    uint32_t m_itemCount;
    uint32_t unk1C;
    uint32_t unk1D;
    uint32_t unk1E;
    uint32_t unk1F;
    CGxPool* m_pool;
    uint32_t m_size;
    uint32_t m_offset;
    bool m_locked;
};
