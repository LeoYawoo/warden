#pragma once

#include <cstdio>

#define WHOA_UNIMPLEMENTED(...)                                                                                 \
    fprintf(stderr, "Function not yet implemented: %s in %s (line %i)\n", __FUNCTION__, __FILE__, __LINE__);    \
    return __VA_ARGS__;                                                                                         \
    (void)0


