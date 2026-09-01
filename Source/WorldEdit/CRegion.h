#pragma once

#include <cstdint>
#include <string>

// Forward declarations
class CTerrain;

// Reverse engineered from Warcraft III binary
// CRegion represents a region in the game world

class CRegion {
public:
    CRegion();
    ~CRegion();

    // Region properties
    int32_t GetRegionId() const;
    void SetRegionId(int32_t id);

    const char* GetRegionName() const;
    void SetRegionName(const char* name);

    // Region bounds
    float GetMinX() const;
    float GetMinY() const;
    float GetMaxX() const;
    float GetMaxY() const;
    void SetBounds(float minX, float minY, float maxX, float maxY);

    // Region state
    bool IsEnabled() const;
    void SetEnabled(bool enabled);

    bool IsVisible() const;
    void SetVisible(bool visible);

    // Point test
    bool ContainsPoint(float x, float y) const;

    // Terrain association
    CTerrain* GetTerrain() const;
    void SetTerrain(CTerrain* terrain);

protected:
    int32_t m_regionId;
    std::string m_regionName;
    float m_minX;
    float m_minY;
    float m_maxX;
    float m_maxY;
    bool m_enabled;
    bool m_visible;
    CTerrain* m_terrain;
};
