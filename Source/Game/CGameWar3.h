#pragma once

#include <cstdint>
#include <string>

// Forward declarations
class CGameState;
class CWorld;

// Reverse engineered from Warcraft III binary
// CGameWar3 manages Warcraft III game

class CGameWar3 {
public:
    CGameWar3();
    ~CGameWar3();

    // Game operations
    bool Initialize();
    void Shutdown();
    bool IsInitialized() const;

    // Game state
    CGameState* GetGameState() const;
    CWorld* GetWorld() const;

    // Game properties
    const char* GetMapName() const;
    void SetMapName(const char* name);

    // Game control
    void StartGame();
    void EndGame();
    bool IsGameRunning() const;

protected:
    bool m_initialized;
    CGameState* m_gameState;
    CWorld* m_world;
    std::string m_mapName;
    bool m_gameRunning;
};
