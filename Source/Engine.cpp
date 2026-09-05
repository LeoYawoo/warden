#include "Engine.h"

// Reverse engineered from Warcraft III binary

namespace Engine {

static bool s_initialized = false;

bool Initialize() {
    if (s_initialized) return true;
    s_initialized = true;
    return true;
}

void Shutdown() {
    s_initialized = false;
}

bool IsInitialized() {
    return s_initialized;
}

} // namespace Engine
