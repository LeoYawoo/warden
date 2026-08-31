#pragma once

#include <cstdint>
#include "StormMac/thread/SThread.h"

void *
SCreateThread(uint32_t (*threadProc)(void *), void *threadParam, void *a3, SThread *syncObject, const char *threadName);

uintptr_t SGetCurrentThreadId();

namespace Blizzard {
    namespace Thread {

// Types
        struct ThreadRecord {

            void *unk4;

            uint32_t (*unk8)(void *);

            int32_t unkC;
            int32_t unk10;
            char name;
        };

        struct TLSSlot {

            uint32_t key;


            void (*destructor)(void *);

            bool allocated;
        };

// Functions
        void AllocateLocalStorage(TLSSlot *slot);

        void *
        RegisterLocalStorage(TLSSlot *slot, void *(*constructor)(void *), void *userData, void (*destructor)(void *));

        void SetLocalStorage(const TLSSlot *slot, const void *value);

        bool TLSSlotIsAllocated(const TLSSlot *slot);

    } // namespace Thread
} // namespace Blizzard


