#pragma once

#include <cstdint>

// Forward declarations
class CTerrain;

// Reverse engineered from Warcraft III binary
// CTerrainCliffDoodads manages cliff doodad decorations

class CTerrainCliffDoodads {
public:
    CTerrainCliffDoodads();
    ~CTerrainCliffDoodads();

    // Doodad properties
    int32_t GetDoodadId() const;
    void SetDoodadId(int32_t id);

    int32_t GetDoodadType() const;
    void SetDoodadType(int32_t type);

    // Doodad state
    bool IsActive() const;
    void SetActive(bool active);

    // Terrain association
    CTerrain* GetTerrain() const;
    void SetTerrain(CTerrain* terrain);

protected:
    int32_t m_doodadId;
    int32_t m_doodadType;
    bool m_active;
    CTerrain* m_terrain;
};
