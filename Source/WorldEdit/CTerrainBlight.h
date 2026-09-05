#pragma once

#include <cstdint>
#include "Engine/Source/Terrain/CTerrain.h"

// Reverse engineered from Warcraft III binary
// CTerrainBlight manages terrain blight (corruption) effects

class CTerrainBlight {
public:
    CTerrainBlight();
    ~CTerrainBlight();

    // Blight operations
    void AddBlight(int32_t x, int32_t y, int32_t radius);
    void RemoveBlight(int32_t x, int32_t y, int32_t radius);
    bool HasBlight(int32_t x, int32_t y) const;

    // Blight state
    bool IsEnabled() const;
    void SetEnabled(bool enabled);

    // Terrain association
    CTerrain* GetTerrain() const;
    void SetTerrain(CTerrain* terrain);

protected:
    bool m_enabled;
    CTerrain* m_terrain;
};
