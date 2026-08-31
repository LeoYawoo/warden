#pragma once

#include <cstdint>
#include <windows.h>


class SSyncObject {
public:
    // Member variables
    HANDLE m_opaqueData = nullptr;


    // Member functions
    SSyncObject();

    ~SSyncObject();

    void Close();

    bool Valid();

    uint32_t Wait(uint32_t timeoutMs);
};


