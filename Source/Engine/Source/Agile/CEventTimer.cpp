#include "CEventTimer.h"

// Reverse engineered from Warcraft III binary

CEventTimer::CEventTimer() : TRefCnt(), m_delay(0.0f), m_elapsed(0.0f), m_agent(nullptr), m_active(false) {
    // Virtual table set in constructor
}

CEventTimer::~CEventTimer() {
    // Virtual destructor
}

void CEventTimer::Schedule(float delay, CAgent* agent) {
    m_delay = delay;
    m_elapsed = 0.0f;
    m_agent = agent;
    m_active = true;
}

void CEventTimer::Cancel() {
    m_active = false;
    m_agent = nullptr;
}

bool CEventTimer::HasExpired() const {
    return m_active && (m_elapsed >= m_delay);
}
