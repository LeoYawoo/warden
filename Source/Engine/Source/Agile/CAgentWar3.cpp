#include "CAgentWar3.h"

// Reverse engineered from Warcraft III binary
// Address: 0x7756A3

CAgentWar3::CAgentWar3() : CAgentBaseAbs(), m_unit(nullptr), m_agentId(0) {
    // Virtual table set in constructor
}

CAgentWar3::~CAgentWar3() {
    // Virtual destructor
}

CUnit* CAgentWar3::GetUnit() const {
    return m_unit;
}

void CAgentWar3::SetUnit(CUnit* unit) {
    m_unit = unit;
}

bool CAgentWar3::IsValid() const {
    return m_unit != nullptr;
}

int CAgentWar3::GetAgentId() const {
    return m_agentId;
}
