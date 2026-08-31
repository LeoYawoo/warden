#pragma once

#include <cstdint>

uint32_t SUniSGetUTF8(const uint8_t *strptr, int32_t *chars);

void SUniSPutUTF8(uint32_t c, char *strptr);


