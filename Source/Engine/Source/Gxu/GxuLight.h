#pragma once

#include <cstdint>

// Reverse engineered from Warcraft III binary
// GxuLight manages light sources in the game

class GxuLight {
public:
    GxuLight();
    ~GxuLight();

    // Light properties
    int32_t GetLightId() const;
    void SetLightId(int32_t id);

    // Light type (directional, point, spot)
    int32_t GetLightType() const;
    void SetLightType(int32_t type);

    // Light color
    float GetRed() const;
    float GetGreen() const;
    float GetBlue() const;
    void SetColor(float r, float g, float b);

    // Light intensity
    float GetIntensity() const;
    void SetIntensity(float intensity);

    // Light range
    float GetRange() const;
    void SetRange(float range);

    // Light position
    float GetX() const;
    float GetY() const;
    float GetZ() const;
    void SetPosition(float x, float y, float z);

    // Light direction
    float GetDirX() const;
    float GetDirY() const;
    float GetDirZ() const;
    void SetDirection(float x, float y, float z);

    // Light state
    bool IsEnabled() const;
    void SetEnabled(bool enabled);

protected:
    int32_t m_lightId;
    int32_t m_lightType;
    float m_red;
    float m_green;
    float m_blue;
    float m_intensity;
    float m_range;
    float m_x;
    float m_y;
    float m_z;
    float m_dirX;
    float m_dirY;
    float m_dirZ;
    bool m_enabled;
};
