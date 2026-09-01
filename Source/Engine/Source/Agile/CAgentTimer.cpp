#include "CAgentTimer.h"

// Reverse engineered from Warcraft III binary

CAgentTimer::CAgentTimer() : m_time(0.0f), m_duration(0.0f), m_active(false) {
}

CAgentTimer::CAgentTimer(const CAgentTimer& other)
    : m_time(other.m_time), m_duration(other.m_duration), m_active(other.m_active) {
}

CAgentTimer::~CAgentTimer() {
}

CAgentTimer& CAgentTimer::operator=(const CAgentTimer& other) {
    if (this != &other) {
        m_time = other.m_time;
        m_duration = other.m_duration;
        m_active = other.m_active;
    }
    return *this;
}

void CAgentTimer::EventId() {
    // Handle timer event
}

float CAgentTimer::GetTime() const {
    return m_time;
}

void CAgentTimer::SetTime(float time) {
    m_time = time;
}

bool CAgentTimer::HasExpired() const {
    return m_active && (m_time >= m_duration);
}
