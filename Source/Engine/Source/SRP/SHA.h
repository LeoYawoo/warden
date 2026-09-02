#pragma once

#include <cstdint>
#include <cstring>

// Reverse engineered from Warcraft III binary
// SHA implements SHA-1 hash algorithm for SRP6 authentication

namespace SRP {
    // SHA-1 context structure
    struct SHA_CTX {
        uint32_t state[5];
        uint32_t count[2];
        uint8_t buffer[64];
    };

    // SHA-1 functions
    void SHA_Init(SHA_CTX* ctx);
    void SHA_Update(SHA_CTX* ctx, const uint8_t* data, uint32_t len);
    void SHA_Final(uint8_t digest[20], SHA_CTX* ctx);

    // SHA-1 one-shot function
    void SHA1(const uint8_t* data, uint32_t len, uint8_t digest[20]);

    // SHA-1 utility functions
    void SHA1ToString(const uint8_t digest[20], char* str);
    bool VerifySHA1(const uint8_t* data, uint32_t len, const uint8_t expected[20]);

    // SHA-1 constants
    const uint32_t SHA1_DIGEST_SIZE = 20;
    const uint32_t SHA1_BLOCK_SIZE = 64;
}
