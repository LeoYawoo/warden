#include "CLeaveEvent.h"
#include "CAgent.h"

// Reverse engineered from Warcraft III binary
// Address: 0x739137

CLeaveEvent::CLeaveEvent(CAgent* agent) : CListener(), m_agent(agent) {
    // Virtual table set in constructor
}

CLeaveEvent::~CLeaveEvent() {
    // Virtual destructor
}

CAgent* CLeaveEvent::GetAgent() const {
    return m_agent;
}
