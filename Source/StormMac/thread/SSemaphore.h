#pragma once

#include "storm/thread/SSyncObject.h"
#include <cstdint>

class SSemaphore : public SSyncObject {
public:
    // Member functions
    SSemaphore(uint32_t initialCount, uint32_t maximumCount);

    int32_t Signal(uint32_t count);
};

