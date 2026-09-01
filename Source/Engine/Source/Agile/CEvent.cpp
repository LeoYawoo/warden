#include "CEvent.h"

// Reverse engineered from Warcraft III binary
// Address: 0x74EDDC

CEvent::CEvent(unsigned int eventType, void* data)
    : m_eventType(eventType), m_data(data) {
    // Virtual table set in constructor
}

CEvent::CEvent(const CEvent& other)
    : m_eventType(other.m_eventType), m_data(other.m_data) {
    // Copy constructor
}

CEvent::~CEvent() {
    // Virtual destructor
}

unsigned int CEvent::GetEventType() const {
    return m_eventType;
}

void* CEvent::GetEventData() const {
    return m_data;
}

void CEvent::SetEventData(void* data) {
    m_data = data;
}

bool CEvent::IsValid() const {
    return m_eventType != 0xFFFFFFFF;
}
