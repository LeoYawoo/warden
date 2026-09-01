#include "CEventTimerEvent.h"

// Reverse engineered from Warcraft III binary
// Address: 0x82421B

CEventTimerEvent::CEventTimerEvent() : m_eventData(0) {
    // Virtual table set in constructor
}

CEventTimerEvent::~CEventTimerEvent() {
    // Virtual destructor
}

int CEventTimerEvent::GetEventData() const {
    return m_eventData;
}

void CEventTimerEvent::SetEventData(int data) {
    m_eventData = data;
}
