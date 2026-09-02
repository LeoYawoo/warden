#include "SHA.h"
#include <cstring>
#include <cstdio>

// Reverse engineered from Warcraft III binary
// SHA-1 implementation for SRP6 authentication

namespace SRP {

// SHA-1 helper functions
static inline uint32_t SHA1_RotateLeft(uint32_t value, int count) {
    return (value << count) | (value >> (32 - count));
}

static void SHA1_Transform(uint32_t state[5], const uint8_t block[64]) {
    uint32_t a, b, c, d, e;
    uint32_t w[80];

    // Prepare message schedule
    for (int i = 0; i < 16; i++) {
        w[i] = (block[i * 4] << 24) | (block[i * 4 + 1] << 16) |
                (block[i * 4 + 2] << 8) | block[i * 4 + 3];
    }

    for (int i = 16; i < 80; i++) {
        w[i] = SHA1_RotateLeft(w[i-3] ^ w[i-8] ^ w[i-14] ^ w[i-16], 1);
    }

    // Initialize working variables
    a = state[0];
    b = state[1];
    c = state[2];
    d = state[3];
    e = state[4];

    // Main loop
    for (int i = 0; i < 80; i++) {
        uint32_t f, k;

        if (i < 20) {
            f = (b & c) | ((~b) & d);
            k = 0x5A827999;
        } else if (i < 40) {
            f = b ^ c ^ d;
            k = 0x6ED9EBA1;
        } else if (i < 60) {
            f = (b & c) | (b & d) | (c & d);
            k = 0x8F1BBCDC;
        } else {
            f = b ^ c ^ d;
            k = 0xCA62C1D6;
        }

        uint32_t temp = SHA1_RotateLeft(a, 5) + f + e + k + w[i];
        e = d;
        d = c;
        c = SHA1_RotateLeft(b, 30);
        b = a;
        a = temp;
    }

    // Add compressed chunk to hash value
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    state[4] += e;
}

void SHA_Init(SHA_CTX* ctx) {
    ctx->state[0] = 0x67452301;
    ctx->state[1] = 0xEFCDAB89;
    ctx->state[2] = 0x98BADCFE;
    ctx->state[3] = 0x10325476;
    ctx->state[4] = 0xC3D2E1F0;
    ctx->count[0] = 0;
    ctx->count[1] = 0;
}

void SHA_Update(SHA_CTX* ctx, const uint8_t* data, uint32_t len) {
    uint32_t i = 0;
    uint32_t j = (ctx->count[0] >> 3) & 63;

    ctx->count[0] += len << 3;
    ctx->count[1] += len >> 29;

    if (j + len > 63) {
        memcpy(&ctx->buffer[j], data, 64 - j);
        SHA1_Transform(ctx->state, ctx->buffer);

        for (i = 64 - j; i + 63 < len; i += 64) {
            SHA1_Transform(ctx->state, &data[i]);
        }

        j = 0;
    } else {
        i = 0;
    }

    memcpy(&ctx->buffer[j], &data[i], len - i);
}

void SHA_Final(uint8_t digest[20], SHA_CTX* ctx) {
    uint8_t finalcount[8];
    uint8_t c;

    for (int i = 0; i < 8; i++) {
        finalcount[i] = static_cast<uint8_t>(ctx->count[(i >= 4 ? 0 : 1)] >> ((3 - i & 3) * 8));
    }

    c = 0x80;
    SHA_Update(ctx, &c, 1);

    while ((ctx->count[0] & 504) != 448) {
        c = 0x00;
        SHA_Update(ctx, &c, 1);
    }

    SHA_Update(ctx, finalcount, 8);

    for (int i = 0; i < 20; i++) {
        digest[i] = static_cast<uint8_t>(ctx->state[i >> 2] >> ((3 - (i & 3)) * 8));
    }

    memset(ctx, 0, sizeof(*ctx));
}

void SHA1(const uint8_t* data, uint32_t len, uint8_t digest[20]) {
    SHA_CTX ctx;
    SHA_Init(&ctx);
    SHA_Update(&ctx, data, len);
    SHA_Final(digest, &ctx);
}

void SHA1ToString(const uint8_t digest[20], char* str) {
    for (int i = 0; i < 20; i++) {
        snprintf(str + i * 2, 3, "%02x", digest[i]);
    }
}

bool VerifySHA1(const uint8_t* data, uint32_t len, const uint8_t expected[20]) {
    uint8_t digest[20];
    SHA1(data, len, digest);
    return memcmp(digest, expected, SHA1_DIGEST_SIZE) == 0;
}

} // namespace SRP
