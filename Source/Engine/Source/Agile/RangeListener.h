#pragma once

#include "CListener.h"

// Reverse engineered from Warcraft III binary
// Address: 0x77BFBF
// RangeListener listens to range changes

class RangeListener : public CListener {
public:
    RangeListener();
    virtual ~RangeListener();

    // Callback when range changes
    virtual void OnRangeChanged(float oldRange, float newRange);

    // Get current range
    float GetRange() const;

    // Set range
    void SetRange(float range);

protected:
    float m_range;
};
