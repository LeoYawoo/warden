#include "StormInit.h"
#include "Debug.h"
#include "Error.h"


void BlizzardAssertCallback(const char *a1, const char *a2, const char *a3, uint32_t a4) {
    if (*a2) {
        SErrDisplayError(0, a3, a4, a2, 0, 1, 0x11111111);
    } else {
        SErrDisplayError(0, a3, a4, a1, 0, 1, 0x11111111);
    }
}

void StormInitialize() {
    // TODO
    // SStrInitialize();
    // SErrInitialize();
    // SLogInitialize();
    // SFile::Initialize();

    Blizzard::Debug::SetAssertHandler(BlizzardAssertCallback);
}
