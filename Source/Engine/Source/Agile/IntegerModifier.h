#pragma once

#include "CModifier.h"

// Reverse engineered from Warcraft III binary
// IntegerModifier modifies integer fields
class IntegerModifier : public CModifier {
public:
    IntegerModifier();
    virtual ~IntegerModifier();
};
