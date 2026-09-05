#pragma once
// Reverse engineered from Warcraft III binary

#include <cstdint>

#define ERROR_NOT_ENOUGH_MEMORY 8

void SErrSetLastError(uint32_t errorCode);
uint32_t SErrGetLastError();
