#pragma once

#include <cstdint>
#include "StormMac/Handle.h"


struct HSRGN__;
typedef struct HSRGN__ *HSRGN;

struct HLOCKEDRGN__;
typedef struct HLOCKEDRGN__ *HLOCKEDRGN;


struct RECTF {
    float left;
    float bottom;
    float right;
    float top;
};

