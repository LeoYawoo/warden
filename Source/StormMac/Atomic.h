#pragma once

#include <cstdint>

typedef long ATOMIC32;


ATOMIC32 SInterlockedDecrement(ATOMIC32 *ptr);

ATOMIC32 SInterlockedIncrement(ATOMIC32 *ptr);

namespace Blizzard {
    namespace Lock {
        namespace Atomic {

            int32_t Increment(volatile int32_t *value);

        } // namespace Atomic
    } // namespace Lock
} // namespace Blizzard


