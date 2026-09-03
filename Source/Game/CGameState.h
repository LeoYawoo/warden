#pragma once

#include <cstdint>

// Reverse engineered from Warcraft III binary
// CGameState manages game state

class CGameState {
public:
    CGameState();
    ~CGameState();

    // State operations
    void Initialize();
    void Shutdown();
    bool IsInitialized() const;

    // Game time
    float GetGameTime() const;
    void SetGameTime(float time);
    void UpdateGameTime(float deltaTime);

    // Time of day
    float GetTimeOfDay() const;
    void SetTimeOfDay(float time);
    float TimeOfDayGet() const;

    // Game speed
    float GetGameSpeed() const;
    void SetGameSpeed(float speed);

    // Game state
    bool IsPaused() const;
    void SetPaused(bool paused);

    bool IsLoading() const;
    void SetLoading(bool loading);

protected:
    bool m_initialized;
    float m_gameTime;
    float m_timeOfDay;
    float m_gameSpeed;
    bool m_paused;
    bool m_loading;
};
