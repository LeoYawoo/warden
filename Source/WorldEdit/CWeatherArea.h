#pragma once

#include <cstdint>
#include <string>

// Forward declarations
class CTerrain;

// Reverse engineered from Warcraft III binary
// CWeatherArea manages weather effects in an area

class CWeatherArea {
public:
    CWeatherArea();
    ~CWeatherArea();

    // Area properties
    int32_t GetAreaId() const;
    void SetAreaId(int32_t id);

    const char* GetAreaName() const;
    void SetAreaName(const char* name);

    // Area bounds
    float GetMinX() const;
    float GetMinY() const;
    float GetMaxX() const;
    float GetMaxY() const;
    void SetBounds(float minX, float minY, float maxX, float maxY);

    // Weather state
    bool IsActive() const;
    void SetActive(bool active);

    int32_t GetWeatherType() const;
    void SetWeatherType(int32_t type);

    // Terrain association
    CTerrain* GetTerrain() const;
    void SetTerrain(CTerrain* terrain);

protected:
    int32_t m_areaId;
    std::string m_areaName;
    float m_minX;
    float m_minY;
    float m_maxX;
    float m_maxY;
    bool m_active;
    int32_t m_weatherType;
    CTerrain* m_terrain;
};
