#pragma once

#include <cstdint>
#include <string>
#include <vector>

// Reverse engineered from Warcraft III binary
// CLeaderboardWar3 manages leaderboards

class CLeaderboardWar3 {
public:
    CLeaderboardWar3();
    ~CLeaderboardWar3();

    // Leaderboard properties
    int32_t GetLeaderboardId() const;
    void SetLeaderboardId(int32_t id);

    const char* GetLeaderboardName() const;
    void SetLeaderboardName(const char* name);

    // Leaderboard operations
    void AddEntry(int32_t playerId, int32_t score);
    void RemoveEntry(int32_t playerId);
    void ClearEntries();

    // Leaderboard queries
    size_t GetEntryCount() const;
    int32_t GetEntryPlayerId(size_t index) const;
    int32_t GetEntryScore(size_t index) const;

    // Leaderboard state
    bool IsVisible() const;
    void SetVisible(bool visible);

protected:
    struct LeaderboardEntry {
        int32_t playerId;
        int32_t score;
    };

    int32_t m_leaderboardId;
    std::string m_leaderboardName;
    std::vector<LeaderboardEntry> m_entries;
    bool m_visible;
};
