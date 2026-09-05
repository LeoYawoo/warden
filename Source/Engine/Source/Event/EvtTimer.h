#pragma once

#include <cstdint>
#include "Common/TSTimerPriority.h"

// Reverse engineered from Warcraft III binary
// EvtTimer manages event timers

class EvtTimer {
public:
    EvtTimer();
    ~EvtTimer();

    // Timer operations
    void SetTimeout(float timeout);
    float GetTimeout() const;

    void SetInterval(float interval);
    float GetInterval() const;

    bool HasExpired() const;
    void Reset();

    // Timer state
    bool IsActive() const;
    void SetActive(bool active);

    // Timer update
    void Update(float deltaTime);

    // Timer link for priority queue
    void *link;

    // Target time for scheduling
    TSTimerPriority<uint32_t> targetTime;

protected:
    float m_timeout;
    float m_interval;
    float m_elapsed;
    bool m_active;
};
