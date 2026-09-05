#pragma once

#include <cstdint>

// Engine module header
// Provides core engine functionality

namespace Engine {
    // Engine initialization
    bool Initialize();
    void Shutdown();
    bool IsInitialized();
}
