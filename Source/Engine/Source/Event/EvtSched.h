#pragma once

#include <cstdint>

// Reverse engineered from Warcraft III binary
// EvtSched manages event scheduling

class EvtSched {
public:
    EvtSched();
    ~EvtSched();

    // Scheduler operations
    bool Initialize();
    void Shutdown();
    bool IsInitialized() const;

    // Scheduling
    void ScheduleEvent(int32_t eventType, float delay);
    void CancelEvent(int32_t eventId);

    // Update
    void Update(float deltaTime);

protected:
    bool m_initialized;
};
