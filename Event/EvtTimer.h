#pragma once

#include <cstdint>
#include "Common/TSTimerPriority.h"
#include "Common/TSPriorityQueue.h"
#include "Common/offset_of.h"

class EvtTimer {
public:
    // Member variables
    uint32_t id;
    TSTimerPriority<uint32_t> targetTime;
    float timeout;

    int32_t (*handler)(const void *, void *);

    void *param;

    int32_t (*guidHandler)(const void *, uint64_t, void *);

    uint64_t guidParam;
    void *guidParam2;

    // Constructor
    EvtTimer() : id(0), targetTime(), timeout(0.0f), handler(nullptr), param(nullptr),
                 guidHandler(nullptr), guidParam(0), guidParam2(nullptr) {}

    EvtTimer(uint32_t timerId, float timeoutSec, int32_t (*timerHandler)(const void *, void *), void* timerParam)
        : id(timerId), targetTime(), timeout(timeoutSec), handler(timerHandler), param(timerParam),
          guidHandler(nullptr), guidParam(0), guidParam2(nullptr) {}

    // Check if timer is valid
    bool IsValid() const {
        return handler != nullptr || guidHandler != nullptr;
    }

    // Compare by target time (for priority queue)
    bool operator<(const EvtTimer& other) const {
        return targetTime.m_val < other.targetTime.m_val;
    }

    bool operator>(const EvtTimer& other) const {
        return targetTime.m_val > other.targetTime.m_val;
    }

    bool operator==(const EvtTimer& other) const {
        return id == other.id;
    }

    bool operator!=(const EvtTimer& other) const {
        return id != other.id;
    }

    // Set timeout relative to current time
    void SetTimeout(float seconds, uint32_t currentTime) {
        timeout = seconds;
        targetTime.m_val = currentTime + static_cast<uint32_t>(seconds * 1000.0f);
    }

    // Check if timer has expired
    bool HasExpired(uint32_t currentTime) const {
        return currentTime >= targetTime.m_val;
    }
};

class EvtTimerQueue : public TSPriorityQueue<EvtTimer> {
public:
    EvtTimerQueue()
            : TSPriorityQueue<EvtTimer>(STRUCT_OFFSET(EvtTimer, targetTime)) {};
};


