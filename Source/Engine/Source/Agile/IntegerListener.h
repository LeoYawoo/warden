#pragma once

#include "CListener.h"

// Reverse engineered from Warcraft III binary
// IntegerListener listens to integer field changes
class IntegerListener : public CListener {
public:
    IntegerListener();
    virtual ~IntegerListener();
};
