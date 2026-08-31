#pragma once

#include "Types.h"
#include "Engine/Source/Event/Types.h"
#include <cstdint>

int32_t ConsoleAccessGetEnabled();

void ConsoleAccessSetEnabled(int32_t enable);

int32_t ConsoleGetActive();

KEY ConsoleGetHotKey();

CONSOLERESIZESTATE ConsoleGetResizeState();

void ConsoleSetActive(int32_t active);

void ConsoleSetHotKey(KEY hotkey);

void ConsoleSetResizeState(CONSOLERESIZESTATE state);


