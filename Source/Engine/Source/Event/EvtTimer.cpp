#include "EvtTimer.h"

// Reverse engineered from Warcraft III binary

EvtTimer::EvtTimer()
    : m_timeout(0.0f), m_interval(0.0f), m_elapsed(0.0f), m_active(false) {
}

EvtTimer::~EvtTimer() {}

void EvtTimer::SetTimeout(float timeout) { m_timeout = timeout; }
float EvtTimer::GetTimeout() const { return m_timeout; }

void EvtTimer::SetInterval(float interval) { m_interval = interval; }
float EvtTimer::GetInterval() const { return m_interval; }

bool EvtTimer::HasExpired() const {
    return m_active && m_elapsed >= m_timeout;
}

void EvtTimer::Reset() {
    m_elapsed = 0.0f;
}

bool EvtTimer::IsActive() const { return m_active; }
void EvtTimer::SetActive(bool active) { m_active = active; }

void EvtTimer::Update(float deltaTime) {
    if (m_active) {
        m_elapsed += deltaTime;
    }
}
