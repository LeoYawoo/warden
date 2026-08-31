#pragma once

#include <cstdint>
#include "CAsyncObject.h"

CAsyncObject *AsyncFileReadAllocObject();

void AsyncFileReadDestroyObject(CAsyncObject *object);

void AsyncFileReadInitialize(uint32_t threadSleep, uint32_t handlerTimeout);

void AsyncFileReadObject(CAsyncObject *object, int32_t a2);

