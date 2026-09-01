#pragma once

#include "CPresenceRef.h"

// Reverse engineered from Warcraft III binary
// CAgentField is a field in the agent system
class CAgentField : public CPresenceRef {
public:
    CAgentField();
    CAgentField(const CAgentField& other);
    virtual ~CAgentField();
};
