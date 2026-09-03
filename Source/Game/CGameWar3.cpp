#include "CGameWar3.h"
#include "CGameState.h"

// Reverse engineered from Warcraft III binary

CGameWar3::CGameWar3()
    : m_initialized(false), m_gameState(nullptr), m_world(nullptr),
      m_gameRunning(false) {
}

CGameWar3::~CGameWar3() {
    Shutdown();
}

bool CGameWar3::Initialize() {
    m_gameState = new CGameState();
    m_gameState->Initialize();
    m_initialized = true;
    return true;
}

void CGameWar3::Shutdown() {
    if (m_gameState) {
        delete m_gameState;
        m_gameState = nullptr;
    }
    m_initialized = false;
}

bool CGameWar3::IsInitialized() const { return m_initialized; }

CGameState* CGameWar3::GetGameState() const { return m_gameState; }
CWorld* CGameWar3::GetWorld() const { return m_world; }

const char* CGameWar3::GetMapName() const { return m_mapName.c_str(); }
void CGameWar3::SetMapName(const char* name) { m_mapName = name ? name : ""; }

void CGameWar3::StartGame() { m_gameRunning = true; }
void CGameWar3::EndGame() { m_gameRunning = false; }
bool CGameWar3::IsGameRunning() const { return m_gameRunning; }
