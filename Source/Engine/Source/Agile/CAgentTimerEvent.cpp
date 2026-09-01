#include "CAgentTimerEvent.h"

// Reverse engineered from Warcraft III binary
// Address: 0x847F1F

CAgentTimerEvent::CAgentTimerEvent() : m_eventData(0) {
    // Virtual table set in constructor
}

CAgentTimerEvent::~CAgentTimerEvent() {
    // Virtual destructor
}

int CAgentTimerEvent::GetEventData() const {
    return m_eventData;
}

void CAgentTimerEvent::SetEventData(int data) {
    m_eventData = data;
}
