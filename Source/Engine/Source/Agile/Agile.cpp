#include "Agile.h"

// Reverse engineered from Warcraft III binary

namespace Agile {

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

const char* GetVersion() {
    return "1.0.0";
}

} // namespace Agile
