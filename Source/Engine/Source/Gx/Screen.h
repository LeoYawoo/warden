#pragma once

#include <cstdint>
#include "../Agile/CHandleObject.h"
#include "Common/TSLink.h"
#include "StormMac/Handle.h"
#include "Common/region/Types.h"


typedef HOBJECT HLAYER;

enum SCRNSTOCK {
    STOCK_SYSFONT = 0,
    STOCK_PERFFONT = 1,
    SCRNSTOCKOBJECTS = 2
};

class CILayer : public CHandleObject {
public:
    RECTF rect;
    RECTF visible;
    float zorder;
    uint32_t flags;
    void *param;

    void (*paintfunc)(void *, const RECTF *, const RECTF *, float);

    TSLink<CILayer> zorderlink;
};

class CSRgn {
public:
    HSRGN m_handle;
};

namespace Screen {
    extern int32_t s_captureScreen;
    extern float s_elapsedSec;
    extern int32_t s_presentDisable;
}

int32_t OnPaint(const void *a1, void *a2);

void ILayerInitialize();

void IStockInitialize();

void ScrnInitialize(int32_t a1);

void ScrnLayerCreate(const RECTF *rect, float zOrder, uint32_t flags, void *param,
                     void (*paintFunc)(void *, const RECTF *, const RECTF *, float), HLAYER *layerPtr);

void ScrnLayerSetRect(HLAYER layer, const RECTF *rect);

void ScrnSetStockFont(SCRNSTOCK stockID, const char *fontTexturePath);


