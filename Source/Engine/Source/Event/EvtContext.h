#pragma once

#include <cstdint>
#include "event/EvtHandler.h"
#include "event/EvtKeyDown.h"
#include "event/EvtMessage.h"
#include "event/EvtTimer.h"
#include "event/Types.h"
#include "StormMac/thread/SCritSect.h"
#include "Common/TSExplicitList.h"
#include "Common/instance/TInstanceId.h"
#include "Common/instance/TSingletonInstanceId.h"
#include "Common/prop/Types.h"
#include <storm/Thread.h>
#include "Common/offset_of.h"

class EvtContext : public TSingletonInstanceId<EvtContext, STRUCT_OFFSET(TInstanceId<EvtContext>, m_id)> {
public:
    // Types
    enum SCHEDSTATE {
        SCHEDSTATE_ACTIVE = 0x0,
        SCHEDSTATE_CLOSED = 0x1,
        SCHEDSTATE_DESTROYED = 0x2,
        _UNIQUE_SYMBOL_SCHEDSTATE_96 = 0xFFFFFFFF,
    };

    // Member variables
    SCritSect m_critsect;
    uint32_t m_currTime;
    SCHEDSTATE m_schedState;
    TSTimerPriority<uint32_t> m_schedNextWakeTime;
    uint32_t m_schedLastIdle;
    uint32_t m_schedFlags;
    uint32_t m_schedIdleTime;
    uint32_t m_schedInitialIdleTime;
    uint32_t m_schedWeight;
    uint32_t m_schedSmoothWeight;
    int32_t m_schedRebalance;
    TSExplicitList<EvtHandler, STRUCT_OFFSET(EvtHandler, link)> m_queueHandlerList[EVENTIDS];
    TSExplicitList<EvtMessage, STRUCT_OFFSET(EvtMessage, link)> m_queueMessageList;
    uint32_t m_queueSyncButtonState;
    TSExplicitList<EvtKeyDown, STRUCT_OFFSET(EvtKeyDown, link)> m_queueSyncKeyDownList;
    // TODO
    // EvtIdTable<EvtTimer*> m_timerIdTable;
    EvtTimerQueue m_timerQueue;
    HPROPCONTEXT m_propContext;
    void *m_callContext;
    uint32_t m_startWatchdog;

    // Member functions
    EvtContext(uint32_t flags, uint32_t idleTime, uint32_t schedWeight, void *callContext, int32_t startWatchdog);
};

class EvtContextQueue : public TSPriorityQueue<EvtContext> {
public:
    EvtContextQueue();
};


