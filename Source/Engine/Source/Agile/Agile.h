#pragma once

#include <cstdint>

// Reverse engineered from Warcraft III binary
// Agile module provides agent and property management

namespace Agile {
    // Module initialization
    bool Initialize();
    void Shutdown();
    bool IsInitialized();

    // Version info
    const char* GetVersion();
}
