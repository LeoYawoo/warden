#include "SmartPosition.h"

// Reverse engineered from Warcraft III binary
// Address: 0x77BF67

SmartPosition::SmartPosition() : Position(), m_regionIndex(-1) {
    // Virtual table set in constructor
}

SmartPosition::~SmartPosition() {
    // Virtual destructor
}

bool SmartPosition::IsValid() const {
    return m_regionIndex >= 0;
}

int SmartPosition::GetRegionIndex() const {
    return m_regionIndex;
}

void SmartPosition::SetRegionIndex(int index) {
    m_regionIndex = index;
}
