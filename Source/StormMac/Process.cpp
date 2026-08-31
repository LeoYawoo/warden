#include "Process.h"


#include <windows.h>


void Blizzard::Process::Sleep(uint32_t durationMs) {
    ::Sleep(durationMs);
}
