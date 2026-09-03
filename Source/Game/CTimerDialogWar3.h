#pragma once

#include <cstdint>
#include <string>

// Reverse engineered from Warcraft III binary
// CTimerDialogWar3 manages timer dialogs

class CTimerDialogWar3 {
public:
    CTimerDialogWar3();
    ~CTimerDialogWar3();

    // Dialog operations
    bool Initialize();
    void Shutdown();
    bool IsInitialized() const;

    // Timer properties
    float GetTime() const;
    void SetTime(float time);

    bool IsRunning() const;
    void SetRunning(bool running);

    // Dialog state
    bool IsVisible() const;
    void SetVisible(bool visible);

protected:
    bool m_initialized;
    float m_time;
    bool m_running;
    bool m_visible;
};
