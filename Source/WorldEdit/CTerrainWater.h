#pragma once

#include <cstdint>

// Forward declarations
class CTerrain;

// Reverse engineered from Warcraft III binary
// CTerrainWater manages terrain water rendering

class CTerrainWater {
public:
    CTerrainWater();
    ~CTerrainWater();

    // Water properties
    float GetWaterLevel() const;
    void SetWaterLevel(float level);

    float GetWaterOpacity() const;
    void SetWaterOpacity(float opacity);

    // Water state
    bool IsActive() const;
    void SetActive(bool active);

    bool IsVisible() const;
    void SetVisible(bool visible);

    // Terrain association
    CTerrain* GetTerrain() const;
    void SetTerrain(CTerrain* terrain);

protected:
    float m_waterLevel;
    float m_waterOpacity;
    bool m_active;
    bool m_visible;
    CTerrain* m_terrain;
};
