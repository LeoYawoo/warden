#pragma once

#include <cstdint>

// Forward declarations
class CTerrain;

// Reverse engineered from Warcraft III binary
// CTerrainCliff manages terrain cliff rendering

class CTerrainCliff {
public:
    CTerrainCliff();
    ~CTerrainCliff();

    // Cliff properties
    int32_t GetCliffId() const;
    void SetCliffId(int32_t id);

    int32_t GetCliffLevel() const;
    void SetCliffLevel(int32_t level);

    // Cliff state
    bool IsActive() const;
    void SetActive(bool active);

    // Terrain association
    CTerrain* GetTerrain() const;
    void SetTerrain(CTerrain* terrain);

protected:
    int32_t m_cliffId;
    int32_t m_cliffLevel;
    bool m_active;
    CTerrain* m_terrain;
};
