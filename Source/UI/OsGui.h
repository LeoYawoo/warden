#pragma once

#include <cstdint>

void *OsGuiGetWindow(int32_t type);

bool OsGuiIsModifierKeyDown(int32_t key);

int32_t OsGuiProcessMessage(void *message);

void OsGuiSetGxWindow(void *window);


