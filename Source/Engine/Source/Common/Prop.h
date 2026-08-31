#pragma once


#include "Common/prop/Types.h"

HPROPCONTEXT PropCreateContext();

void *PropGet(PROPERTY id);

HPROPCONTEXT PropGetSelectedContext();

void PropInitialize();

void PropSelectContext(HPROPCONTEXT context);

void PropSet(PROPERTY id, void *value);


