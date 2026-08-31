#pragma once

#include <cstdint>
#include "region/Types.h"

void SRgnCombineRectf(HSRGN handle, RECTF *rect, void *param, int32_t combineMode);

void SRgnCreate(HSRGN *handlePtr, uint32_t reserved);

void SRgnDelete(HSRGN handle);

void SRgnGetBoundingRectf(HSRGN handle, RECTF *rect);


