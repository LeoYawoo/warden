#pragma once

#include <cstdint>

void HMAC_SHA1(const uint8_t *key, uint32_t keyLen, const uint8_t *data, uint32_t dataLen, uint8_t *out);


