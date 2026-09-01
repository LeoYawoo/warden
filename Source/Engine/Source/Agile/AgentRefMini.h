#pragma once

// Forward declarations
class CAgent;

// Reverse engineered from Warcraft III binary
// Address: 0x76F170
// AgentRefMini is a mini reference to an agent

class AgentRefMini {
public:
    AgentRefMini();
    ~AgentRefMini();

    // Assignment operator
    AgentRefMini& operator=(CAgent* agent);

    // Check if assigned
    bool IsAssigned() const;

    // Get agent
    CAgent* GetAgent() const;

    // Check if same agent
    bool SameAgent(const CAgent* agent) const;

private:
    CAgent* m_agent;
};
