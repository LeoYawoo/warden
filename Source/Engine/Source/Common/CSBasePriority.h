#pragma once

#include <cstdint>

class CSBasePriorityQueue;

class CSBasePriority {
public:
    // Member variables
    CSBasePriorityQueue *m_queue;
    uint32_t m_index;

    // Member functions
    virtual bool Compare(CSBasePriority *a) = 0;

    void Unlink();

    void Relink();
};


