#pragma once


#include <cstdint>
#include "../Tempest/CRect.h"
#include "../Tempest/CImVector.h"
#include "CGxCaps.h"
#include "CGxFormat.h"
#include "Types.h"

class QOpenGLFunctions;

using namespace Tempest;
extern const char **g_gxShaderProfileNames[GxShTargets_Last];

const CGxCaps &GxCaps();

// GL functions accessor (set by WardenWindow after context creation)
QOpenGLFunctions *GxGetGLFunctions();
void GxSetGLFunctions(QOpenGLFunctions *funcs);

bool GxCapsWindowHasFocus(int32_t);

void GxCapsWindowSize(CRect &);

void GxFormatColor(CImVector &);


