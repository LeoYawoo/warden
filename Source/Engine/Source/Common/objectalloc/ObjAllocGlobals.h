#pragma once

#include "CObjectHeapList.h"
#include "StormMac/thread/SCritSect.h"
#include "Common/TSGrowableArray.h"
#include <StormMac/Thread.h>

class OBJALLOCGLOBALS {
public:
    // Static variables
    static OBJALLOCGLOBALS s_globals;
    static SCritSect s_globalsLock;

    // Member variables
    TSGrowableArray <CObjectHeapList> objects;
};

OBJALLOCGLOBALS *GetObjAllocGlobals();

void ReleaseObjAllocGlobals();


