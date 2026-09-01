#pragma once

#include "Common/TRefCnt.h"

// Forward declarations
class CAgent;

// Reverse engineered from Warcraft III binary
// CEventTimer manages timed events for agents
class CEventTimer : public TRefCnt {
public:
    CEventTimer();
    virtual ~CEventTimer();

    void Schedule(float delay, CAgent* agent);
    void Cancel();
    bool HasExpired() const;

private:
    float m_delay;
    float m_elapsed;
    CAgent* m_agent;
    bool m_active;
};
