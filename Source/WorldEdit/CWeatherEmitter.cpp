#include "CWeatherEmitter.h"

// Reverse engineered from Warcraft III binary

CWeatherEmitter::CWeatherEmitter()
    : m_emitterId(0),
      m_enabled(false),
      m_playing(false),
      m_emissionRate(0.0f),
      m_lifetime(0.0f),
      m_speed(0.0f),
      m_spread(0.0f),
      m_x(0.0f),
      m_y(0.0f),
      m_area(nullptr) {
}

CWeatherEmitter::~CWeatherEmitter() {
}

int32_t CWeatherEmitter::GetEmitterId() const {
    return m_emitterId;
}

void CWeatherEmitter::SetEmitterId(int32_t id) {
    m_emitterId = id;
}

const char* CWeatherEmitter::GetEmitterName() const {
    return m_emitterName.c_str();
}

void CWeatherEmitter::SetEmitterName(const char* name) {
    if (name) {
        m_emitterName = name;
    } else {
        m_emitterName.clear();
    }
}

bool CWeatherEmitter::IsEnabled() const {
    return m_enabled;
}

void CWeatherEmitter::SetEnabled(bool enabled) {
    m_enabled = enabled;
}

bool CWeatherEmitter::IsPlaying() const {
    return m_playing;
}

void CWeatherEmitter::SetPlaying(bool playing) {
    m_playing = playing;
}

float CWeatherEmitter::GetEmissionRate() const {
    return m_emissionRate;
}

void CWeatherEmitter::SetEmissionRate(float rate) {
    m_emissionRate = rate;
}

float CWeatherEmitter::GetLifetime() const {
    return m_lifetime;
}

void CWeatherEmitter::SetLifetime(float lifetime) {
    m_lifetime = lifetime;
}

float CWeatherEmitter::GetSpeed() const {
    return m_speed;
}

void CWeatherEmitter::SetSpeed(float speed) {
    m_speed = speed;
}

float CWeatherEmitter::GetSpread() const {
    return m_spread;
}

void CWeatherEmitter::SetSpread(float spread) {
    m_spread = spread;
}

float CWeatherEmitter::GetX() const {
    return m_x;
}

float CWeatherEmitter::GetY() const {
    return m_y;
}

void CWeatherEmitter::SetPosition(float x, float y) {
    m_x = x;
    m_y = y;
}

CWeatherArea* CWeatherEmitter::GetArea() const {
    return m_area;
}

void CWeatherEmitter::SetArea(CWeatherArea* area) {
    m_area = area;
}
