#pragma once

#include <cstdint>

// Reverse engineered from Warcraft III binary
// NetCommon provides common network utilities

namespace NetCommon {
    // Network initialization
    bool Initialize();
    void Shutdown();

    // Network utilities
    uint32_t HostToNetwork32(uint32_t value);
    uint16_t HostToNetwork16(uint16_t value);
    uint32_t NetworkToHost32(uint32_t value);
    uint16_t NetworkToHost16(uint16_t value);

    // IP address utilities
    bool ParseIP(const char* str, uint32_t* ip);
    void FormatIP(uint32_t ip, char* str, uint32_t strSize);

    // Checksum utilities
    uint16_t CalculateChecksum(const void* data, uint32_t size);
}
