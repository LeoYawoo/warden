#pragma once

#include <cstdint>

// Forward declarations
class CTerrain;

// Reverse engineered from Warcraft III binary
// CTerrainBounds manages terrain boundary calculations

class CTerrainBounds {
public:
    CTerrainBounds();
    ~CTerrainBounds();

    // Bounds operations
    void CalculateBounds(const CTerrain* terrain);
    bool IsInBounds(float x, float y) const;

    // Getters
    float GetMinX() const;
    float GetMinY() const;
    float GetMaxX() const;
    float GetMaxY() const;
    float GetWidth() const;
    float GetHeight() const;

protected:
    float m_minX;
    float m_minY;
    float m_maxX;
    float m_maxY;
};
