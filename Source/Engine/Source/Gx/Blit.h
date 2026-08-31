#pragma once

#include "Types.h"
#include <cstdint>
#include "../Tempest/C2iVector.h>

using namespace Tempest;

typedef void (*BLIT_FUNCTION)(const C2iVector &, const void *, uint32_t, void *, uint32_t);

void Blit(const C2iVector &, BlitAlpha, const void *, uint32_t, BlitFormat, void *, uint32_t, BlitFormat);

BlitFormat GxGetBlitFormat(EGxTexFormat);


