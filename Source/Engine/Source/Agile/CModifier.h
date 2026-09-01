#pragma once

#include "CRelation.h"

// Reverse engineered from Warcraft III binary
// CModifier is a base class for modifying agent fields
class CModifier : public CRelation {
public:
    CModifier();
    virtual ~CModifier();
};
