#pragma once

#include <cstdint>
#include "StormMac/thread/SThread.h"


class CAsyncObject;

class CAsyncQueue;

class CAsyncThread : public TSLinkedNode<CAsyncThread> {
public:
    // Member variables
    SThread thread;
    CAsyncQueue *queue;
    CAsyncObject *currentObject;
};


