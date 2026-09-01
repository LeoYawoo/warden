#include "RangeListener.h"

// Reverse engineered from Warcraft III binary
// Address: 0x77BFBF

RangeListener::RangeListener() : CListener(), m_range(0.0f) {
    // Virtual table set in constructor
}

RangeListener::~RangeListener() {
    // Virtual destructor
}

void RangeListener::OnRangeChanged(float oldRange, float newRange) {
    // Default implementation does nothing
    (void)oldRange;
    (void)newRange;
}

float RangeListener::GetRange() const {
    return m_range;
}

void RangeListener::SetRange(float range) {
    float oldRange = m_range;
    m_range = range;
    OnRangeChanged(oldRange, range);
}
