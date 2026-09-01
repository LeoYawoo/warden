#pragma once

#include "CRelation.h"

// Reverse engineered from Warcraft III binary
// CListener is a base class for listening to agent field changes
class CListener : public CRelation {
public:
    CListener();
    virtual ~CListener();
};
