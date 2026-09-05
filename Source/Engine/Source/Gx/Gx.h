#pragma once


#include <cstdint>
#include "../Tempest/CRect.h"
#include "../Tempest/CImVector.h"
#include "CGxCaps.h"
#include "CGxFormat.h"
#include "Types.h"

using namespace Tempest;
extern const char **g_gxShaderProfileNames[GxShTargets_Last];

const CGxCaps &GxCaps();

bool GxCapsWindowHasFocus(int32_t);

void GxCapsWindowSize(CRect &);

void GxFormatColor(CImVector &);


