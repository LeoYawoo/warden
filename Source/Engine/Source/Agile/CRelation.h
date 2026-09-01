#pragma once

#include "CAgentField.h"

// Reverse engineered from Warcraft III binary
// CRelation represents a relationship between agents
class CRelation : public CAgentField {
public:
    CRelation();
    virtual ~CRelation();
};
