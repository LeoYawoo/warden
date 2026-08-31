#pragma once

#include <cstdint>

class CM2Shared;

class CM2Cache {
public:
    // Static variables
    static CM2Cache s_cache;

    // Member variables
    uint32_t m_initialized = 0;
    uint32_t m_flags = 0;

    // Member functions
    void BeginThread(void (*callback)(void *), void *arg);

    CM2Shared *CreateShared(const char *, uint32_t);

    void GarbageCollect(int32_t a2);

    int32_t Initialize(uint32_t flags);

    void UpdateShared();

    void WaitThread();
};

