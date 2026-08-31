#pragma once

#include <cstdint>

class CGxFont;

uint32_t InternalGetMaxCharsWithinWidth(CGxFont*, const char*, float, float, uint32_t, float*, uint32_t, float, float, uint32_t*, float*, float*);

void InternalGetTextExtent(CGxFont*, const char*, uint32_t, float, float*, uint32_t, float, float);


