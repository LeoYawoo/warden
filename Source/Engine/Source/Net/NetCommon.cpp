#include "NetCommon.h"
#include <cstring>
#include <cstdio>

// Reverse engineered from Warcraft III binary

namespace NetCommon {

bool Initialize() {
    // TODO: Initialize Winsock or other network library
    return true;
}

void Shutdown() {
    // TODO: Shutdown network library
}

uint32_t HostToNetwork32(uint32_t value) {
    return ((value & 0xFF) << 24) | ((value & 0xFF00) << 8) |
           ((value & 0xFF0000) >> 8) | ((value & 0xFF000000) >> 24);
}

uint16_t HostToNetwork16(uint16_t value) {
    return ((value & 0xFF) << 8) | ((value & 0xFF00) >> 8);
}

uint32_t NetworkToHost32(uint32_t value) {
    return HostToNetwork32(value);
}

uint16_t NetworkToHost16(uint16_t value) {
    return HostToNetwork16(value);
}

bool ParseIP(const char* str, uint32_t* ip) {
    if (!str || !ip) return false;
    // TODO: Implement IP parsing
    *ip = 0;
    return true;
}

void FormatIP(uint32_t ip, char* str, uint32_t strSize) {
    if (!str) return;
    snprintf(str, strSize, "%d.%d.%d.%d",
             (ip >> 24) & 0xFF, (ip >> 16) & 0xFF,
             (ip >> 8) & 0xFF, ip & 0xFF);
}

uint16_t CalculateChecksum(const void* data, uint32_t size) {
    if (!data || size == 0) return 0;

    const uint16_t* ptr = static_cast<const uint16_t*>(data);
    uint32_t sum = 0;

    while (size > 1) {
        sum += *ptr++;
        size -= 2;
    }

    if (size > 0) {
        sum += *reinterpret_cast<const uint8_t*>(ptr);
    }

    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);

    return static_cast<uint16_t>(~sum);
}

} // namespace NetCommon
