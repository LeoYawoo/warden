#pragma once

#include "net/grunt/Grunt.h"
#include "StormMac/thread/SEvent.h"
#include "StormMac/thread/SThread.h"
#include "StormMac/thread/SCritSect.h"
#include "Common/TSExplicitList.h"
#include "../Event/Event.h"
#include "Common/TSLink.h"


class Grunt::Timer {
public:
    // Types
    class Event {
    public:
        // Member variables
        TSLink<Event> m_link;
        uint32_t m_schedTime;
        uint32_t m_interval;

        // Virtual methods
        virtual void Call() = 0;
    };

    // Static functions
    static uint32_t ThreadProc(void *param);

    // Member variables
    SEvent m_event = SEvent(0, 0);
    SThread m_thread;
    SCritSect m_critSect;
    STORM_EXPLICIT_LIST(Event, m_link) m_eventList;

    // Member functions
    Timer();

    void Insert(Event &newEvent);

    uint32_t Pump();
};


