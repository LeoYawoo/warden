#include "AgentRefMini.h"

// Reverse engineered from Warcraft III binary
// Address: 0x76F170

AgentRefMini::AgentRefMini() : m_agent(nullptr) {
}

AgentRefMini::~AgentRefMini() {
}

AgentRefMini& AgentRefMini::operator=(CAgent* agent) {
    m_agent = agent;
    return *this;
}

bool AgentRefMini::IsAssigned() const {
    return m_agent != nullptr;
}

CAgent* AgentRefMini::GetAgent() const {
    return m_agent;
}

bool AgentRefMini::SameAgent(const CAgent* agent) const {
    return m_agent == agent;
}
