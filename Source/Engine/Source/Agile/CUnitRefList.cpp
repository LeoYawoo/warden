#include "CUnitRefList.h"

// Reverse engineered from Warcraft III binary
// Address: 0x7756D7

CUnitRefList::CUnitRefList() : m_unit(nullptr), m_next(nullptr), m_agentRef() {
    // Virtual table set in constructor
}

CUnitRefList::~CUnitRefList() {
    // Virtual destructor
}

void CUnitRefList::Initialize(CUnit* unit, CUnitRefList* next) {
    m_unit = unit;
    m_next = next;
}

void CUnitRefList::Bind(CAgentBaseAbs* agent) {
    // Bind to agent
    (void)agent;
}

void CUnitRefList::BindMini(CAgentBaseAbs* agent) {
    // Bind mini to agent
    (void)agent;
}

void CUnitRefList::Checklog(HSLOG* log) {
    // Check log for errors
    (void)log;
}

void CUnitRefList::LoadMini(void* data) {
    // Load mini data
    (void)data;
}

void CUnitRefList::SaveMini(void* data) {
    // Save mini data
    (void)data;
}

CUnit* CUnitRefList::GetUnit() const {
    return m_unit;
}

CUnitRefList* CUnitRefList::GetNext() const {
    return m_next;
}
