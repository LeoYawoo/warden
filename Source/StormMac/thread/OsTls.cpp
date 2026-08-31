#include "OsTls.h"
#include <windows.h>

int32_t OsTlsAlloc() {
    return TlsAlloc();
}

void *OsTlsGetValue(uint32_t tlsIndex) {
    return TlsGetValue(tlsIndex);
}

int32_t OsTlsSetValue(uint32_t tlsIndex, void *tlsValue) {
    return TlsSetValue(tlsIndex, tlsValue);
}
