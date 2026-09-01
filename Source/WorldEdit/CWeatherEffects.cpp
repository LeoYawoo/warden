#include "CWeatherEffects.h"
#include "CWeatherArea.h"
#include "CWeatherEmitter.h"
#include <algorithm>

// Reverse engineered from Warcraft III binary

CWeatherEffects::CWeatherEffects()
    : m_effectsId(0),
      m_enabled(false),
      m_playing(false),
      m_intensity(0.0f),
      m_duration(0.0f),
      m_elapsedTime(0.0f) {
}

CWeatherEffects::~CWeatherEffects() {
}

int32_t CWeatherEffects::GetEffectsId() const {
    return m_effectsId;
}

void CWeatherEffects::SetEffectsId(int32_t id) {
    m_effectsId = id;
}

const char* CWeatherEffects::GetEffectsName() const {
    return m_effectsName.c_str();
}

void CWeatherEffects::SetEffectsName(const char* name) {
    if (name) {
        m_effectsName = name;
    } else {
        m_effectsName.clear();
    }
}

bool CWeatherEffects::IsEnabled() const {
    return m_enabled;
}

void CWeatherEffects::SetEnabled(bool enabled) {
    m_enabled = enabled;
}

bool CWeatherEffects::IsPlaying() const {
    return m_playing;
}

void CWeatherEffects::SetPlaying(bool playing) {
    m_playing = playing;
}

float CWeatherEffects::GetIntensity() const {
    return m_intensity;
}

void CWeatherEffects::SetIntensity(float intensity) {
    m_intensity = intensity;
}

float CWeatherEffects::GetDuration() const {
    return m_duration;
}

void CWeatherEffects::SetDuration(float duration) {
    m_duration = duration;
}

void CWeatherEffects::AddArea(CWeatherArea* area) {
    if (area) {
        m_areas.push_back(area);
    }
}

void CWeatherEffects::RemoveArea(CWeatherArea* area) {
    auto it = std::find(m_areas.begin(), m_areas.end(), area);
    if (it != m_areas.end()) {
        m_areas.erase(it);
    }
}

size_t CWeatherEffects::GetAreaCount() const {
    return m_areas.size();
}

void CWeatherEffects::AddEmitter(CWeatherEmitter* emitter) {
    if (emitter) {
        m_emitters.push_back(emitter);
    }
}

void CWeatherEffects::RemoveEmitter(CWeatherEmitter* emitter) {
    auto it = std::find(m_emitters.begin(), m_emitters.end(), emitter);
    if (it != m_emitters.end()) {
        m_emitters.erase(it);
    }
}

size_t CWeatherEffects::GetEmitterCount() const {
    return m_emitters.size();
}

void CWeatherEffects::Update(float deltaTime) {
    if (!m_enabled || !m_playing) {
        return;
    }

    m_elapsedTime += deltaTime;

    // Check if duration expired
    if (m_duration > 0.0f && m_elapsedTime >= m_duration) {
        m_playing = false;
        return;
    }

    // Update emitters
    for (auto* emitter : m_emitters) {
        if (emitter && emitter->IsEnabled()) {
            // Update emitter logic here
        }
    }
}
