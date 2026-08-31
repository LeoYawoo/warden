#pragma once

#include <cstdint>

struct SARC4Key {
    uint8_t state[256];
    uint8_t x;
    uint8_t y;
};