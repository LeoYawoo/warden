#pragma once

#include "Common/TRefCnt.h"

// Reverse engineered from Warcraft III binary
// Address: 0x847F1F
// CAgentTimerEvent is an event for agent timers
class CAgentTimerEvent {
public:
    CAgentTimerEvent();
    virtual ~CAgentTimerEvent();

    int GetEventData() const;
    void SetEventData(int data);

private:
    // Virtual table pointer
    int m_eventData;  // offset +16
};
