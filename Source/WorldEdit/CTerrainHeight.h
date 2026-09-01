#pragma once

#include <cstdint>

// Forward declarations
class CTerrain;

// Reverse engineered from Warcraft III binary
// CTerrainHeight manages terrain height operations

class CTerrainHeight {
public:
    CTerrainHeight();
    ~CTerrainHeight();

    // Height operations
    float GetHeight(int32_t x, int32_t y) const;
    void SetHeight(int32_t x, int32_t y, float height);
    void SmoothHeight(int32_t x, int32_t y, int32_t radius);

    // Height queries
    float GetMinHeight() const;
    float GetMaxHeight() const;
    float GetAverageHeight() const;

    // Terrain association
    CTerrain* GetTerrain() const;
    void SetTerrain(CTerrain* terrain);

protected:
    CTerrain* m_terrain;
};
