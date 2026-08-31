#pragma once

#include <cstdint>
#include "win/SRWLock.h"


class CSRWLock {
public:
    // Member variables
    SRWLock::SURWLOCK m_opaqueData;

    // Member functions
    void Enter(int32_t forwriting);

    void Leave(int32_t fromwriting);
};

