#pragma once

#include <cstdint>

// Forward declarations
class CTerrain;

// Reverse engineered from Warcraft III binary
// CTerrainRamp manages terrain ramp (slope) operations

class CTerrainRamp {
public:
    CTerrainRamp();
    ~CTerrainRamp();

    // Ramp properties
    int32_t GetRampId() const;
    void SetRampId(int32_t id);

    float GetSlope() const;
    void SetSlope(float slope);

    // Ramp state
    bool IsActive() const;
    void SetActive(bool active);

    // Terrain association
    CTerrain* GetTerrain() const;
    void SetTerrain(CTerrain* terrain);

protected:
    int32_t m_rampId;
    float m_slope;
    bool m_active;
    CTerrain* m_terrain;
};
