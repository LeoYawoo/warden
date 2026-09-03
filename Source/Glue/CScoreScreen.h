#pragma once

#include <cstdint>
#include <string>
#include <vector>

// Reverse engineered from Warcraft III binary
// CScoreScreen manages the score screen

class CScoreScreen {
public:
    CScoreScreen();
    ~CScoreScreen();

    // Score screen operations
    bool Initialize();
    void Shutdown();
    bool IsInitialized() const;

    // Score data
    void AddPlayerScore(int32_t playerId, const char* name, int32_t score);
    void ClearScores();

    // Score queries
    size_t GetPlayerCount() const;
    const char* GetPlayerName(size_t index) const;
    int32_t GetPlayerScore(size_t index) const;

    // Score screen state
    bool IsVisible() const;
    void SetVisible(bool visible);

protected:
    struct PlayerScore {
        int32_t playerId;
        std::string name;
        int32_t score;
    };

    bool m_initialized;
    bool m_visible;
    std::vector<PlayerScore> m_scores;
};
