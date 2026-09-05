#pragma once

#include "datamgr/CDataMgr.h"
#include "StormMac/Handle.h"
#include "Engine/Source/Tempest/C3Vector.h"

typedef HOBJECT HDATAMGR;
using namespace Tempest;

void DataMgrGetCoord(HDATAMGR mgr, uint32_t fieldId, C3Vector *coord);

void DataMgrSetCoord(HDATAMGR mgr, uint32_t fieldId, const C3Vector &coord, uint32_t coordFlags);

void DataMgrSetFloat(HDATAMGR mgr, uint32_t fieldId, float val);


