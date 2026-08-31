#pragma once


#include <cstdint>
#include "Common/TSGrowableArray.h"

struct CStringElement {
    CStringElement *next;
    char str;
};

class CStringMemory : public TSGrowableArray<void *> {
public:
    // Member variables
    uintptr_t m_free;
    uintptr_t m_end;

    // Member functions
    void AllocateBlock(size_t blockSize);

    CStringElement *New(const char *str);
};
