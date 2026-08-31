#pragma once

#include <cstdint>
#include "TSGrowableArray.h"

class CSBasePriority;

class CSBasePriorityQueue : public TSGrowableArray<void *> {
public:
    // Member variables
    uint32_t m_linkOffset;

    // Member functions
    void *Dequeue();

    void Enqueue(void *val);

    CSBasePriority *Link(uint32_t index) const;

    void Remove(uint32_t index);

    void SetLink(uint32_t index);

    void *Top();
};


