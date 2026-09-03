#include "CAgentBase.h"

// Reverse engineered from Warcraft III binary

CAgentBase::CAgentBase() : m_agentId(0), m_initialized(false) {}
CAgentBase::~CAgentBase() {}

int32_t CAgentBase::GetAgentId() const { return m_agentId; }
void CAgentBase::SetAgentId(int32_t id) { m_agentId = id; }

bool CAgentBase::IsInitialized() const { return m_initialized; }
void CAgentBase::SetInitialized(bool initialized) { m_initialized = initialized; }

void CAgentBase::Update(float deltaTime) {
    // Update agent logic
    (void)deltaTime;
}

void CAgentBase::Reset() {
    m_agentId = 0;
    m_initialized = false;
}
