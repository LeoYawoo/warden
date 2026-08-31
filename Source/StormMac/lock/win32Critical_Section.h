//
// Created by liuyawu on 2024/3/31.
//

#pragma once

#include <windows.h>

class win32Critical_Section {
// simple class to wrap a CRITICAL_SECTION object with lock/unlock operations
public:
    CRITICAL_SECTION cs;
public:
    win32Critical_Section() { InitializeCriticalSection(&cs); }

    ~win32Critical_Section() { DeleteCriticalSection(&cs); }

    void lock() { EnterCriticalSection(&cs); }

    void unlock() { LeaveCriticalSection(&cs); }

};
