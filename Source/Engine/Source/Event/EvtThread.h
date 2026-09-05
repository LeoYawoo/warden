#pragma once

#include <cstdint>
#include "Common/TSLinkedNode.h"
#include "event/EvtContext.h"
#include "StormMac/thread/SEvent.h"
#include <StormMac/Thread.h>

class EvtThread : public TSLinkedNode<EvtThread> {
public:
    // Member variables
    uint32_t m_threadSlot;
    uint32_t m_threadCount;
    uint32_t m_weightTotal;
    uint32_t m_weightAvg;
    uint32_t m_contextCount;
    uint32_t m_rebalance;
    SEvent m_wakeEvent = SEvent(0, 0);
    EvtContextQueue m_contextQueue;

    // Member functions
    EvtThread();
};


