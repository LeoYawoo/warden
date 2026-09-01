#include "AgentRef.h"

// Reverse engineered from Warcraft III binary
// Address: 0x738EAF

AgentRef::AgentRef() : CAgentField(), m_agent(nullptr) {
    // Virtual table set in constructor
}

AgentRef::~AgentRef() {
    // Virtual destructor
}

CAgent* AgentRef::GetAgent() const {
    return m_agent;
}

void AgentRef::SetAgent(CAgent* agent) {
    m_agent = agent;
}

bool AgentRef::IsValid() const {
    return m_agent != nullptr;
}

void AgentRef::Clear() {
    m_agent = nullptr;
}
