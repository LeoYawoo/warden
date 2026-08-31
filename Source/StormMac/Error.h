#pragma once

#include <cstdint>
#include <WinError.h>


#if defined(NDEBUG)
#define STORM_ASSERT(x)                          \
    (void)0
#else
#define STORM_ASSERT(x)                          \
    if (!(x)) {                                  \
        SErrPrepareAppFatal(__FILE__, __LINE__); \
        SErrDisplayAppFatal(#x);                 \
    }                                            \
    (void)0
#endif

#define STORM_VALIDATE(x, y, ...)                \
    if (!(x)) {                                  \
        SErrSetLastError(y);                     \
        return __VA_ARGS__;                      \
    }                                            \
    (void)0

void SErrDisplayAppFatal(const char *format, ...);

int32_t SErrDisplayError(uint32_t errorcode, const char *filename, int32_t linenumber, const char *description,
                         int32_t recoverable, uint32_t exitcode, uint32_t a7);

int32_t SErrDisplayErrorFmt(uint32_t errorcode, const char *filename, int32_t linenumber, int32_t recoverable,
                            uint32_t exitcode, const char *format, ...);

void SErrPrepareAppFatal(const char *filename, int32_t linenumber);

void SErrSetLastError(uint32_t errorcode);

uint32_t SErrGetLastError();


