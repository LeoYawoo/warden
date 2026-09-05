#pragma once

#include <cstdint>
#include "Common/DataMgr.h"
#include "../Tempest/CRect.h"
#include "../Tempest/C2Vector.h"

using namespace Tempest;

typedef HDATAMGR HCAMERA;


HCAMERA CameraCreate();

void CameraSetupScreenProjection(const CRect &, const C2Vector &, float, int32_t);

void CameraSetupWorldProjection(HCAMERA camera, const CRect &projectionRect, uint32_t flags);


