#pragma once

#include <cstdint>

// Reverse engineered from Warcraft III binary
// Lightning manages lightning bolt effects

class Lightning {
public:
    Lightning();
    ~Lightning();

    // Lightning properties
    int32_t GetLightningId() const;
    void SetLightningId(int32_t id);

    // Lightning state
    bool IsActive() const;
    void SetActive(bool active);

    // Lightning parameters
    float GetWidth() const;
    void SetWidth(float width);

    float GetRed() const;
    float GetGreen() const;
    float GetBlue() const;
    void SetColor(float r, float g, float b);

    // Lightning position
    float GetStartX() const;
    float GetStartY() const;
    float GetStartZ() const;
    void SetStartPoint(float x, float y, float z);

    float GetEndX() const;
    float GetEndY() const;
    float GetEndZ() const;
    void SetEndPoint(float x, float y, float z);

protected:
    int32_t m_lightningId;
    bool m_active;
    float m_width;
    float m_red;
    float m_green;
    float m_blue;
    float m_startX;
    float m_startY;
    float m_startZ;
    float m_endX;
    float m_endY;
    float m_endZ;
};
