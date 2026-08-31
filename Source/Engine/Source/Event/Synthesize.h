#pragma once

#include <cstdint>

class EvtContext;

void SynthesizeDestroy(EvtContext* context);

void SynthesizeIdle(EvtContext* context, uint32_t currTime, float elapsedSec);

int32_t SynthesizeInitialize(EvtContext* context);

void SynthesizePaint(EvtContext* context);

void SynthesizePoll(EvtContext* context);


