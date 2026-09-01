#pragma once

#include "CModifier.h"

// Reverse engineered from Warcraft III binary
// FloatModifier modifies float fields
class FloatModifier : public CModifier {
public:
    FloatModifier();
    virtual ~FloatModifier();
};
