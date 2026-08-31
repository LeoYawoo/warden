#include "Time.h"


#include <windows.h>


uint64_t OsGetAsyncTimeMs() {

    return GetTickCount();


}

uint64_t OsGetAsyncTimeMsPrecise() {

    // TODO QueryPerformanceCounter implementation
    return OsGetAsyncTimeMs();

}

void OsSleep(uint32_t duration) {
    Sleep(duration);
}
