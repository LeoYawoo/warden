#pragma once

#include "event/Types.h"

class EvtContext;

void IEvtQueueDispatch(EvtContext* context, EVENTID id, const void* data);

void IEvtQueueDispatchAll(EvtContext* context);

void IEvtQueueRegister(EvtContext* context, EVENTID id, int32_t (*handler)(const void*, void*), void* param, float priority);


