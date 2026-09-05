#pragma once

#include "Engine/Source/Agile/CAgent.h"

// Forward declarations
class CUnit;

// Reverse engineered from Warcraft III binary
// Address: 0x7756A3
// CAgentWar3 is the Warcraft III specific agent class

class CAgentWar3 : public CAgentBaseAbs {
public:
    CAgentWar3();
    virtual ~CAgentWar3();

    // Get associated unit
    CUnit* GetUnit() const;

    // Set associated unit
    void SetUnit(CUnit* unit);

    // Check if agent is valid
    bool IsValid() const;

    // Get agent ID
    int GetAgentId() const;

protected:
    CUnit* m_unit;   // offset +32
    int m_agentId;   // offset +32
};
