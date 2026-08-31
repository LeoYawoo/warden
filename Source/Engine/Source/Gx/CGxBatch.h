#pragma once

#include "Types.h"
#include <cstdint>

class CGxBatch {
public:
    // Member variables
    EGxPrim m_primType;
    uint32_t m_start;
    uint32_t m_count;
    uint16_t m_minIndex;
    uint16_t m_maxIndex;
};


