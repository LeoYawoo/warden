#pragma once


#include "SFile.h"
#include "Common/TSLink.h"

class CAsyncQueue;

class CAsyncObject {
public:
    // Member variables
    SFile *file;
    void *buffer;
    uint32_t size;
    void *userArg;

    void (*userPostloadCallback)(void *);

    void (*userFailedCallback)(void *);

    CAsyncQueue *queue;
    void *ptr1C;
    uint8_t priority;
    uint8_t isProcessed;
    uint8_t isRead;
    uint8_t isCurrent;
    uint8_t char24;
    uint8_t char25;
    uint8_t padding[2];
    TSLink <CAsyncObject> link;
};


