#pragma once

#include "CListener.h"

// Reverse engineered from Warcraft III binary
// FloatListener listens to float field changes
class FloatListener : public CListener {
public:
    FloatListener();
    virtual ~FloatListener();
};
