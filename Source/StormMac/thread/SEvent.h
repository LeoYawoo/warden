#pragma once

#include "storm/thread/SSyncObject.h"
#include <cstdint>

class SEvent : public SSyncObject {
public:
    // Member functions
    SEvent(int32_t manualReset, int32_t initialValue);

    int32_t Reset();

    int32_t Set();
};

