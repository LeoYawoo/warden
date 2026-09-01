#pragma once

#include "Common/TRefCnt.h"

// Reverse engineered from Warcraft III binary
// Address: 0x82421B
// CEventTimerEvent is an event for event timers
class CEventTimerEvent {
public:
    CEventTimerEvent();
    virtual ~CEventTimerEvent();

    int GetEventData() const;
    void SetEventData(int data);

private:
    // Virtual table pointer
    int m_eventData;  // offset +16
};
