#pragma once

#include "shader/CGxShader.h"
#include "shader/CShaderEffect.h"
#include "shader/CShaderEffectManager.h"
#include "Types.h"
#include <cstdint>

char *GxShaderConstantsLock(EGxShTarget target);

void GxShaderConstantsSet(EGxShTarget, uint32_t, const float *, uint32_t);

void GxShaderConstantsUnlock(EGxShTarget target, uint32_t index, uint32_t count);


