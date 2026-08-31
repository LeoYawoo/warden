#pragma once
#include "crypto/SARC4Key.h"

void SARC4PrepareKey(const void* data, uint32_t len, SARC4Key* key);

void SARC4ProcessBuffer(void* data, uint32_t len, const SARC4Key* inKey, SARC4Key* outKey);