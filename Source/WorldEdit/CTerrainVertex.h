#pragma once

#include <cstdint>

// Forward declarations
class CTerrain;

// Reverse engineered from Warcraft III binary
// CTerrainVertex manages terrain vertex operations

class CTerrainVertex {
public:
    CTerrainVertex();
    ~CTerrainVertex();

    // Vertex properties
    float GetX() const;
    float GetY() const;
    float GetZ() const;
    void SetPosition(float x, float y, float z);

    // Vertex normal
    float GetNormalX() const;
    float GetNormalY() const;
    float GetNormalZ() const;
    void SetNormal(float x, float y, float z);

    // Vertex state
    bool IsActive() const;
    void SetActive(bool active);

    // Terrain association
    CTerrain* GetTerrain() const;
    void SetTerrain(CTerrain* terrain);

protected:
    float m_x;
    float m_y;
    float m_z;
    float m_normalX;
    float m_normalY;
    float m_normalZ;
    bool m_active;
    CTerrain* m_terrain;
};
