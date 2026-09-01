#pragma once

#include "CAgent.h"
#include "AgentRefMini.h"

// Forward declarations
class CUnit;
class HSLOG;

// Reverse engineered from Warcraft III binary
// Address: 0x7756D7
// CUnitRefList manages a list of unit references

class CUnitRefList {
public:
    CUnitRefList();
    virtual ~CUnitRefList();

    // Initialize with unit and next list
    void Initialize(CUnit* unit, CUnitRefList* next);

    // Bind to agent
    void Bind(CAgentBaseAbs* agent);
    void BindMini(CAgentBaseAbs* agent);

    // Check log for errors
    void Checklog(HSLOG* log);

    // Load/Save
    void LoadMini(void* data);
    void SaveMini(void* data);

    // Get unit
    CUnit* GetUnit() const;

    // Get next in list
    CUnitRefList* GetNext() const;

protected:
    // Virtual table pointer
    CUnit* m_unit;           // offset +4
    CUnitRefList* m_next;    // offset +8
    AgentRefMini m_agentRef; // offset +36
};
