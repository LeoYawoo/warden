#include "CTimerDialogWar3.h"

// Reverse engineered from Warcraft III binary

CTimerDialogWar3::CTimerDialogWar3()
    : m_initialized(false), m_time(0.0f), m_running(false), m_visible(false) {
}

CTimerDialogWar3::~CTimerDialogWar3() { Shutdown(); }

bool CTimerDialogWar3::Initialize() {
    m_initialized = true;
    return true;
}

void CTimerDialogWar3::Shutdown() {
    m_initialized = false;
}

bool CTimerDialogWar3::IsInitialized() const { return m_initialized; }

float CTimerDialogWar3::GetTime() const { return m_time; }
void CTimerDialogWar3::SetTime(float time) { m_time = time; }

bool CTimerDialogWar3::IsRunning() const { return m_running; }
void CTimerDialogWar3::SetRunning(bool running) { m_running = running; }

bool CTimerDialogWar3::IsVisible() const { return m_visible; }
void CTimerDialogWar3::SetVisible(bool visible) { m_visible = visible; }
