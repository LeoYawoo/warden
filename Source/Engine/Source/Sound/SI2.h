#pragma once

#include "SI2Script.h"
#include "UI/Types.h"
#include <cstdint>

class SI2 {
public:
    // Static variables
    static FrameScript_Method s_ScriptFunctions[NUM_SCRIPT_FUNCTIONS_SI2];

    // Static functions
    static void RegisterScriptFunctions();
};

