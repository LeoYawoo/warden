#pragma once


#include <cstdint>
#include "SSyncObject.h"

class SThread : public SSyncObject {
public:
    // Static functions
    static int32_t Create(uint32_t (*threadProc)(void *), void *param, SThread &thread, char *threadName, uint32_t a5);
};


