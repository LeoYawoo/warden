#pragma once


#include <cstdint>

namespace Blizzard {
    namespace System_Debug {

// Types
        typedef void (*AssertCallback)(const char *, const char *, const char *, uint32_t);

// Variables
        extern AssertCallback s_assertCallback;

    } // namespace System_Debug
} // namespace Blizzard


