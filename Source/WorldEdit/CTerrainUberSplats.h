#pragma once

#include <cstdint>
#include <string>

// Forward declarations
class CTerrain;

// Reverse engineered from Warcraft III binary
// CTerrainUberSplats manages terrain uber splat (decal) operations

class CTerrainUberSplats {
public:
    CTerrainUberSplats();
    ~CTerrainUberSplats();

    // UberSplat properties
    int32_t GetSplatId() const;
    void SetSplatId(int32_t id);

    const char* GetSplatName() const;
    void SetSplatName(const char* name);

    float GetScale() const;
    void SetScale(float scale);

    // UberSplat state
    bool IsActive() const;
    void SetActive(bool active);

    // Terrain association
    CTerrain* GetTerrain() const;
    void SetTerrain(CTerrain* terrain);

protected:
    int32_t m_splatId;
    std::string m_splatName;
    float m_scale;
    bool m_active;
    CTerrain* m_terrain;
};
