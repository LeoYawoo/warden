#pragma once

#include "CAgentField.h"
#include "CListener.h"
#include "CModifier.h"
#include "CAgentTimer.h"

// Reverse engineered from Warcraft III binary
// CAgent is the base class for all agents in the game

// Forward declarations
class CAgentField;

// CAgentBaseAbs - Base class for all agent types
// Inherits from NIpse::CRlAgent
class CAgentBaseAbs {
public:
    CAgentBaseAbs();
    virtual ~CAgentBaseAbs();

    static CAgentBaseAbs* Constants_(CAgentBaseAbs* agent);

protected:
    // Virtual table pointer
    // Offset +4: constants
    // Offset +8: constants
};

// CAgent - Main agent class
class CAgent : public CAgentBaseAbs {
public:
    CAgent();
    virtual ~CAgent();

    // Agent operations
    void BindMini(CAgentBaseAbs* base);
};

// CAgentPtr - Smart pointer for agents
template<typename T>
class CAgentPtr {
public:
    CAgentPtr();
    ~CAgentPtr();

    T* Get() const;
    void Set(T* agent);
    void Release();

private:
    T* m_agent;
};
