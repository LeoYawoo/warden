#pragma once

#include <cstdint>
#include <vector>

// Reverse engineered from Warcraft III binary
// CFogOfWarMap manages fog of war

class CFogOfWarMap {
public:
    CFogOfWarMap();
    ~CFogOfWarMap();

    // Map operations
    bool Initialize(int32_t width, int32_t height);
    void Shutdown();
    bool IsInitialized() const;

    // Fog operations
    void SetFogState(int32_t x, int32_t y, int32_t state);
    int32_t GetFogState(int32_t x, int32_t y) const;

    // Map properties
    int32_t GetWidth() const;
    int32_t GetHeight() const;

    // Utility
    void WorldToCell(float worldX, float worldY, int32_t& cellX, int32_t& cellY) const;

protected:
    bool m_initialized;
    int32_t m_width;
    int32_t m_height;
    std::vector<uint8_t> m_fogData;
};
