#include "CFramePoint.h"

// Reverse engineered from Warcraft III binary

CFramePoint::CFramePoint() : m_x(0), m_y(0), m_frame(nullptr), m_offsetX(0), m_offsetY(0) {}
CFramePoint::~CFramePoint() {}

float CFramePoint::GetX() const { return m_x; }
float CFramePoint::GetY() const { return m_y; }
void CFramePoint::SetPosition(float x, float y) { m_x = x; m_y = y; }

CFrame* CFramePoint::GetFrame() const { return m_frame; }
void CFramePoint::SetFrame(CFrame* frame) { m_frame = frame; }

float CFramePoint::GetOffsetX() const { return m_offsetX; }
float CFramePoint::GetOffsetY() const { return m_offsetY; }
void CFramePoint::SetOffset(float x, float y) { m_offsetX = x; m_offsetY = y; }
