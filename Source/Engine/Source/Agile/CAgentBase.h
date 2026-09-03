#pragma once

#include <cstdint>

// Reverse engineered from Warcraft III binary
// CAgentBase provides base agent functionality

class CAgentBase {
public:
    CAgentBase();
    virtual ~CAgentBase();

    // Agent properties
    int32_t GetAgentId() const;
    void SetAgentId(int32_t id);

    // Agent state
    bool IsInitialized() const;
    void SetInitialized(bool initialized);

    // Agent operations
    virtual void Update(float deltaTime);
    virtual void Reset();

protected:
    int32_t m_agentId;
    bool m_initialized;
};
