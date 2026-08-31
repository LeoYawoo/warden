#pragma once

#include "Atomic.h"
#include <cstdint>


#include <windows.h>


namespace Blizzard {
    namespace Lock {

// Types


        typedef CRITICAL_SECTION Mutex;


        struct DoOnceData {
            bool done;
            int32_t atomic;
        };

// Functions
        void DoOnce(DoOnceData &a1, void (*a2)(void *), void *a3);

        int32_t MutexCreate(Mutex &mutex);

        int32_t MutexEnter(Mutex &mutex);

        int32_t MutexLeave(Mutex &mutex);

    } // namespace Lock
} // namespace Blizzard


