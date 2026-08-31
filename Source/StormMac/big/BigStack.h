#pragma once


#include <cstdint>
#include "BigBuffer.h"

class BigStack {
public:
    // Static variables
    const static uint32_t SIZE = 16;

    // Member variables
    BigBuffer m_buffer[SIZE];
    uint32_t m_used = 0;

    // Member functions
    BigBuffer &Alloc(uint32_t *count);

    void Free(uint32_t count);

    BigBuffer &MakeDistinct(BigBuffer &orig, int32_t required);

    void UnmakeDistinct(BigBuffer &orig, BigBuffer &distinct);
};


