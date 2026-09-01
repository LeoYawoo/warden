#pragma once

#include <cstdint>
#include <string>
#include <vector>

// Forward declarations
class CWeatherArea;
class CWeatherEmitter;

// Reverse engineered from Warcraft III binary
// CWeatherEffects manages weather effects in the game

class CWeatherEffects {
public:
    CWeatherEffects();
    ~CWeatherEffects();

    // Effects properties
    int32_t GetEffectsId() const;
    void SetEffectsId(int32_t id);

    const char* GetEffectsName() const;
    void SetEffectsName(const char* name);

    // Effects state
    bool IsEnabled() const;
    void SetEnabled(bool enabled);

    bool IsPlaying() const;
    void SetPlaying(bool playing);

    // Effects parameters
    float GetIntensity() const;
    void SetIntensity(float intensity);

    float GetDuration() const;
    void SetDuration(float duration);

    // Weather areas
    void AddArea(CWeatherArea* area);
    void RemoveArea(CWeatherArea* area);
    size_t GetAreaCount() const;

    // Weather emitters
    void AddEmitter(CWeatherEmitter* emitter);
    void RemoveEmitter(CWeatherEmitter* emitter);
    size_t GetEmitterCount() const;

    // Update effects
    void Update(float deltaTime);

protected:
    int32_t m_effectsId;
    std::string m_effectsName;
    bool m_enabled;
    bool m_playing;
    float m_intensity;
    float m_duration;
    float m_elapsedTime;
    std::vector<CWeatherArea*> m_areas;
    std::vector<CWeatherEmitter*> m_emitters;
};
