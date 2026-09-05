#pragma once

#include <cstdint>
#include "Common/TSLinkedNode.h"
#include "Common/TSList.h"
#include "CGxString.h"

// Reverse engineered from Warcraft III binary
// CGxStringBatch manages a batch of rendered text strings

class CGxStringBatch : public TSLinkedNode<CGxStringBatch> {
public:
    CGxStringBatch();
    ~CGxStringBatch();

    void AddString(CGxString* string);
    void Clear();
    void RenderBatch();

    // IDA reverse-engineered members
    uint32_t m_flags;
    TSList<CGxString, TSGetLink<CGxString>> m_fontBatch;
};
