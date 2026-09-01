#pragma once

#include "CAgentField.h"

// Forward declarations
class CAgent;

// Reverse engineered from Warcraft III binary
// Address: 0x738EAF
// AgentRef is a reference to an agent

class AgentRef : public CAgentField {
public:
    AgentRef();
    virtual ~AgentRef();

    // Get referenced agent
    CAgent* GetAgent() const;

    // Set referenced agent
    void SetAgent(CAgent* agent);

    // Check if reference is valid
    bool IsValid() const;

    // Clear reference
    void Clear();

protected:
    CAgent* m_agent;  // Custom field
};
