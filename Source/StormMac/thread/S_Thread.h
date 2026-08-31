#pragma once

#include "storm/thread/SThread.h"
#include <cstdint>
#include <windows.h>


typedef SThread SyncObjectData;

struct SThreadParmBlock {
    uint32_t (*threadProc)(void *);

    void *threadParam;
    uint32_t threadID;
    HANDLE threadH;
};

class S_Thread {
public:
    // Types
    struct SThreadTrack {
        int32_t suspended;
        int32_t live;
        uint32_t threadId;
        HANDLE threadH;
        char name[16];
    };

    // Static variables
    static int32_t s_numthreads;
    static int32_t s_maxthreads;
    static uint32_t s_threadID;
    static SThreadTrack s_threads[1024];

    // Static functions

    static DWORD s_SLaunchThread(void *threadParam);
};


