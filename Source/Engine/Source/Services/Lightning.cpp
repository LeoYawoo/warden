#include "Lightning.h"

// Reverse engineered from Warcraft III binary

Lightning::Lightning()
    : m_lightningId(0), m_active(false), m_width(1.0f),
      m_red(1.0f), m_green(1.0f), m_blue(1.0f),
      m_startX(0), m_startY(0), m_startZ(0),
      m_endX(0), m_endY(0), m_endZ(0) {}

Lightning::~Lightning() {}

int32_t Lightning::GetLightningId() const { return m_lightningId; }
void Lightning::SetLightningId(int32_t id) { m_lightningId = id; }
bool Lightning::IsActive() const { return m_active; }
void Lightning::SetActive(bool active) { m_active = active; }
float Lightning::GetWidth() const { return m_width; }
void Lightning::SetWidth(float width) { m_width = width; }
float Lightning::GetRed() const { return m_red; }
float Lightning::GetGreen() const { return m_green; }
float Lightning::GetBlue() const { return m_blue; }
void Lightning::SetColor(float r, float g, float b) { m_red = r; m_green = g; m_blue = b; }
float Lightning::GetStartX() const { return m_startX; }
float Lightning::GetStartY() const { return m_startY; }
float Lightning::GetStartZ() const { return m_startZ; }
void Lightning::SetStartPoint(float x, float y, float z) { m_startX = x; m_startY = y; m_startZ = z; }
float Lightning::GetEndX() const { return m_endX; }
float Lightning::GetEndY() const { return m_endY; }
float Lightning::GetEndZ() const { return m_endZ; }
void Lightning::SetEndPoint(float x, float y, float z) { m_endX = x; m_endY = y; m_endZ = z; }
