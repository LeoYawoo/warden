#pragma once

#include <cstdint>
#include <string>

// Forward declarations
class CWeatherArea;

// Reverse engineered from Warcraft III binary
// CWeatherEmitter manages weather particle emission

class CWeatherEmitter {
public:
    CWeatherEmitter();
    ~CWeatherEmitter();

    // Emitter properties
    int32_t GetEmitterId() const;
    void SetEmitterId(int32_t id);

    const char* GetEmitterName() const;
    void SetEmitterName(const char* name);

    // Emitter state
    bool IsEnabled() const;
    void SetEnabled(bool enabled);

    bool IsPlaying() const;
    void SetPlaying(bool playing);

    // Emitter parameters
    float GetEmissionRate() const;
    void SetEmissionRate(float rate);

    float GetLifetime() const;
    void SetLifetime(float lifetime);

    float GetSpeed() const;
    void SetSpeed(float speed);

    float GetSpread() const;
    void SetSpread(float spread);

    // Emitter position
    float GetX() const;
    float GetY() const;
    void SetPosition(float x, float y);

    // Weather area association
    CWeatherArea* GetArea() const;
    void SetArea(CWeatherArea* area);

protected:
    int32_t m_emitterId;
    std::string m_emitterName;
    bool m_enabled;
    bool m_playing;
    float m_emissionRate;
    float m_lifetime;
    float m_speed;
    float m_spread;
    float m_x;
    float m_y;
    CWeatherArea* m_area;
};
