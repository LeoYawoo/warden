#pragma once

#include <cstdint>
#include "Types.h"
#include "Common/Hashkey.h"
#include "Common/TSGrowableArray.h"
#include "Common/TSHashObject.h"


struct SOURCE {
    RECTF rect;
    void *param;
    int32_t sequence;
    uint32_t flags;
};

struct FOUNDPARAM {
    void *param;
    int32_t sequence;
};

class RGN : public TSHashObject<RGN, HASHKEY_NONE> {
public:
    // Member variables
    TSGrowableArray <SOURCE> source;
    TSGrowableArray <RECTF> combined;
    TSGrowableArray <FOUNDPARAM> foundparams;
    RECTF foundparamsrect;
    int32_t sequence;
    int32_t dirty;
};


