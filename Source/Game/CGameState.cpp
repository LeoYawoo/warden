#include "CGameState.h"

// Reverse engineered from Warcraft III binary

CGameState::CGameState()
    : m_initialized(false), m_gameTime(0), m_timeOfDay(0),
      m_gameSpeed(1.0f), m_paused(false), m_loading(false) {
}

CGameState::~CGameState() {
    Shutdown();
}

void CGameState::Initialize() {
    m_initialized = true;
    m_gameTime = 0;
    m_timeOfDay = 0;
    m_gameSpeed = 1.0f;
    m_paused = false;
    m_loading = false;
}

void CGameState::Shutdown() {
    m_initialized = false;
}

bool CGameState::IsInitialized() const { return m_initialized; }

float CGameState::GetGameTime() const { return m_gameTime; }
void CGameState::SetGameTime(float time) { m_gameTime = time; }

void CGameState::UpdateGameTime(float deltaTime) {
    if (!m_paused) {
        m_gameTime += deltaTime * m_gameSpeed;
    }
}

float CGameState::GetTimeOfDay() const { return m_timeOfDay; }
void CGameState::SetTimeOfDay(float time) { m_timeOfDay = time; }

float CGameState::TimeOfDayGet() const { return m_timeOfDay; }

float CGameState::GetGameSpeed() const { return m_gameSpeed; }
void CGameState::SetGameSpeed(float speed) { m_gameSpeed = speed; }

bool CGameState::IsPaused() const { return m_paused; }
void CGameState::SetPaused(bool paused) { m_paused = paused; }

bool CGameState::IsLoading() const { return m_loading; }
void CGameState::SetLoading(bool loading) { m_loading = loading; }
