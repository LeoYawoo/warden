#pragma once

#include "CListener.h"

// Forward declarations
class CAgent;

// Reverse engineered from Warcraft III binary
// Address: 0x739137
// CLeaveEvent is triggered when an agent leaves
class CLeaveEvent : public CListener {
public:
    CLeaveEvent(CAgent* agent);
    virtual ~CLeaveEvent();

    CAgent* GetAgent() const;

private:
    CAgent* m_agent;  // offset +16
};
