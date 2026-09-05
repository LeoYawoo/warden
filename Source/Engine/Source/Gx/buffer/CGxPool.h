#pragma once

#include <cstdint>
#include "Common/TSExplicitList.h"
#include "CGxBuf.h"

// Reverse engineered from Warcraft III binary
// CGxPool manages graphics memory pools

enum EGxPoolTarget {
    GxPoolTarget_Vertex = 0,
    GxPoolTarget_Index = 1,
    GxPoolTargets_Last = 2
};

enum EGxPoolUsage {
    GxPoolUsage_Static = 0,
    GxPoolUsage_Dynamic = 1,
    GxPoolUsage_Stream = 2
};

enum EGxPoolHintBits {
    GxPoolHintBits_None = 0,
    GxPoolHintBit_Unk1 = 1,
    GxPoolHintBit_Unk2 = 2,
    GxPoolHintBit_Unk3 = 4
};

class CGxPool : public TSLinkedNode<CGxPool> {
public:
    CGxPool();
    CGxPool(EGxPoolTarget target, EGxPoolUsage usage, uint32_t size, EGxPoolHintBits hint, const char* name);
    ~CGxPool();

    // Pool properties
    EGxPoolUsage GetUsage() const;
    void SetUsage(EGxPoolUsage usage);

    // IDA reverse-engineered members
    STORM_EXPLICIT_LIST(CGxBuf, m_linktofull) m_bufList;
    uint32_t m_size;
    EGxPoolTarget m_target;
    EGxPoolUsage m_usage;
};
