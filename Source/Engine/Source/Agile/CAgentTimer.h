#pragma once

// Reverse engineered from Warcraft III binary
// CAgentTimer is a timer for agent operations

class CAgentTimer {
public:
    CAgentTimer();
    CAgentTimer(const CAgentTimer& other);
    ~CAgentTimer();

    CAgentTimer& operator=(const CAgentTimer& other);

    void EventId();

    // Timer operations
    float GetTime() const;
    void SetTime(float time);
    bool HasExpired() const;

private:
    float m_time;
    float m_duration;
    bool m_active;
};
