#pragma once

#include <cstdint>

// Forward declarations
class CFrame;

// Reverse engineered from Warcraft III binary
// CFramePoint defines a point on a frame

class CFramePoint {
public:
    CFramePoint();
    ~CFramePoint();

    // Point properties
    float GetX() const;
    float GetY() const;
    void SetPosition(float x, float y);

    // Point frame
    CFrame* GetFrame() const;
    void SetFrame(CFrame* frame);

    // Point offset
    float GetOffsetX() const;
    float GetOffsetY() const;
    void SetOffset(float x, float y);

protected:
    float m_x;
    float m_y;
    CFrame* m_frame;
    float m_offsetX;
    float m_offsetY;
};
