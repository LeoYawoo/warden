#include "GxuLight.h"

// Reverse engineered from Warcraft III binary

GxuLight::GxuLight()
    : m_lightId(0), m_lightType(0),
      m_red(1.0f), m_green(1.0f), m_blue(1.0f),
      m_intensity(1.0f), m_range(1000.0f),
      m_x(0.0f), m_y(0.0f), m_z(0.0f),
      m_dirX(0.0f), m_dirY(0.0f), m_dirZ(-1.0f),
      m_enabled(true) {}

GxuLight::~GxuLight() {}

int32_t GxuLight::GetLightId() const { return m_lightId; }
void GxuLight::SetLightId(int32_t id) { m_lightId = id; }
int32_t GxuLight::GetLightType() const { return m_lightType; }
void GxuLight::SetLightType(int32_t type) { m_lightType = type; }
float GxuLight::GetRed() const { return m_red; }
float GxuLight::GetGreen() const { return m_green; }
float GxuLight::GetBlue() const { return m_blue; }
void GxuLight::SetColor(float r, float g, float b) { m_red = r; m_green = g; m_blue = b; }
float GxuLight::GetIntensity() const { return m_intensity; }
void GxuLight::SetIntensity(float intensity) { m_intensity = intensity; }
float GxuLight::GetRange() const { return m_range; }
void GxuLight::SetRange(float range) { m_range = range; }
float GxuLight::GetX() const { return m_x; }
float GxuLight::GetY() const { return m_y; }
float GxuLight::GetZ() const { return m_z; }
void GxuLight::SetPosition(float x, float y, float z) { m_x = x; m_y = y; m_z = z; }
float GxuLight::GetDirX() const { return m_dirX; }
float GxuLight::GetDirY() const { return m_dirY; }
float GxuLight::GetDirZ() const { return m_dirZ; }
void GxuLight::SetDirection(float x, float y, float z) { m_dirX = x; m_dirY = y; m_dirZ = z; }
bool GxuLight::IsEnabled() const { return m_enabled; }
void GxuLight::SetEnabled(bool enabled) { m_enabled = enabled; }
