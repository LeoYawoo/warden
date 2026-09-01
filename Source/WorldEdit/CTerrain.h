#pragma once

#include <cstdint>
#include <vector>

// Forward declarations
class CWeatherArea;

// Reverse engineered from Warcraft III binary
// CTerrain manages the game terrain

class CTerrain {
public:
    CTerrain();
    ~CTerrain();

    // Terrain properties
    int32_t GetWidth() const;
    int32_t GetHeight() const;
    int32_t GetTileSize() const;

    // Terrain height
    float GetHeight(int32_t x, int32_t y) const;
    void SetHeight(int32_t x, int32_t y, float height);

    // Terrain flags
    uint32_t GetFlags(int32_t x, int32_t y) const;
    void SetFlags(int32_t x, int32_t y, uint32_t flags);

    // Water
    bool IsWater(int32_t x, int32_t y) const;
    void SetWater(int32_t x, int32_t y, bool water);

    // Bounds
    bool InBounds(float x, float y) const;
    bool InBoundsInt(int32_t x, int32_t y) const;

    // Weather
    void AddWeatherArea(CWeatherArea* area);
    void RemoveWeatherArea(CWeatherArea* area);

    // Initialization
    void Initialize(int32_t width, int32_t height, int32_t tileSize);
    void Shutdown();

protected:
    int32_t m_width;
    int32_t m_height;
    int32_t m_tileSize;
    std::vector<float> m_heightMap;
    std::vector<uint32_t> m_flagMap;
    std::vector<bool> m_waterMap;
    std::vector<CWeatherArea*> m_weatherAreas;
};
