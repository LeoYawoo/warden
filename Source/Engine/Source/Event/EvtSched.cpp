#include "EvtSched.h"

// Reverse engineered from Warcraft III binary

EvtSched::EvtSched() : m_initialized(false) {}
EvtSched::~EvtSched() { Shutdown(); }

bool EvtSched::Initialize() {
    m_initialized = true;
    return true;
}

void EvtSched::Shutdown() {
    m_initialized = false;
}

bool EvtSched::IsInitialized() const { return m_initialized; }

void EvtSched::ScheduleEvent(int32_t eventType, float delay) {
    (void)eventType; (void)delay;
    // Schedule event
}

void EvtSched::CancelEvent(int32_t eventId) {
    (void)eventId;
    // Cancel event
}

void EvtSched::Update(float deltaTime) {
    (void)deltaTime;
    // Update scheduled events
}
