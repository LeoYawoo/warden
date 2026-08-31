#pragma once

#include <cstdint>
#include <windows.h>

struct Rect {
    int16_t top;
    int16_t left;
    int16_t bottom;
    int16_t right;
};


int32_t OsGetDefaultWindowRect(RECT *rect);

Rect *GetSavedWindowBounds();

Rect *GetSavedZoomedWindowBounds();

void SetSavedWindowBounds(Rect rect);

void SetSavedZoomedWindowBounds(Rect rect);


