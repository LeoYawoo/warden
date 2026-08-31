#pragma once

#include <cstdlib>

void *luaM_initPool();

void *luaM_reallocPool(void *ud, void *ptr, size_t osize, size_t nsize);

