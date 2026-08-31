#pragma once


#include <cstdint>
#include "Engine/Source/Event/Event.h"

class CVar;

namespace Client {
    extern CVar *g_accountListVar;
    extern HEVENTCONTEXT g_clientEventContext;
}

void ClientPostClose(int32_t a1);

int32_t InitializeGlobal();

void WowClientInit();
