#pragma once

#include "Common/TSExplicitList.h"
#include "CRenderBatch.h"
#include "CSimpleFrame.h"
#include <cstdint>

enum FRAMEPOINT;
class CSimpleFrame;
class CFrameStrataNode {
public:
    // Member variables
    STORM_EXPLICIT_LIST(CSimpleFrame, m_strataLink) pendingFrames;
    STORM_EXPLICIT_LIST(CSimpleFrame, m_strataLink) frames;
    CSimpleFrame *pendingFrame = nullptr;
    CRenderBatch batches[5];
    int32_t batchDirty = 0;
    STORM_EXPLICIT_LIST(CRenderBatch, renderLink) renderList;

    // Member functions
    int32_t BuildBatches();

    void OnLayerUpdate(float elapsedSec);

    bool RemoveFrame(CSimpleFrame *frame);
};

class CFrameStrata {
public:
    // Member variables
    int32_t batchDirty = 0;
    int32_t levelsDirty = 0;
    uint32_t topLevel = 0;
    TSFixedArray<CFrameStrataNode *> levels;

    // Member functions
    void AddFrame(CSimpleFrame *);

    int32_t BuildBatches(int32_t a2);

    void CheckOcclusion();

    int32_t FrameOccluded(CSimpleFrame *frame);

    void OnLayerUpdate(float elapsedSec);

    void RemoveFrame(CSimpleFrame *frame);

    void RenderBatches();
};


