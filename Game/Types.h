#pragma once

#include <cstdint>

enum COLOR_T {
    DEFAULT_COLOR,
    INPUT_COLOR,
    ECHO_COLOR,
    ERROR_COLOR,
    WARNING_COLOR,
    GLOBAL_COLOR,
    ADMIN_COLOR,
    HIGHLIGHT_COLOR,
    BACKGROUND_COLOR,
    NUM_COLORTYPES,
};

inline const char* GetColorTypeName(COLOR_T color) {
    static const char* names[] = {
        "DEFAULT", "INPUT", "ECHO", "ERROR", "WARNING",
        "GLOBAL", "ADMIN", "HIGHLIGHT", "BACKGROUND"
    };
    if (color >= 0 && color < NUM_COLORTYPES) return names[color];
    return "UNKNOWN";
}

enum CONSOLERESIZESTATE {
    CS_NONE,
    CS_STRETCH,
    NUM_CONSOLERESIZESTATES,
};

inline const char* GetConsoleResizeStateName(CONSOLERESIZESTATE state) {
    static const char* names[] = {"NONE", "STRETCH"};
    if (state >= 0 && state < NUM_CONSOLERESIZESTATES) return names[state];
    return "UNKNOWN";
}


