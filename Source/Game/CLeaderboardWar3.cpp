#include "CLeaderboardWar3.h"
#include <algorithm>

// Reverse engineered from Warcraft III binary

CLeaderboardWar3::CLeaderboardWar3() : m_leaderboardId(0), m_visible(true) {}
CLeaderboardWar3::~CLeaderboardWar3() {}

int32_t CLeaderboardWar3::GetLeaderboardId() const { return m_leaderboardId; }
void CLeaderboardWar3::SetLeaderboardId(int32_t id) { m_leaderboardId = id; }

const char* CLeaderboardWar3::GetLeaderboardName() const { return m_leaderboardName.c_str(); }
void CLeaderboardWar3::SetLeaderboardName(const char* name) { m_leaderboardName = name ? name : ""; }

void CLeaderboardWar3::AddEntry(int32_t playerId, int32_t score) {
    m_entries.push_back({playerId, score});
    std::sort(m_entries.begin(), m_entries.end(),
        [](const LeaderboardEntry& a, const LeaderboardEntry& b) { return a.score > b.score; });
}

void CLeaderboardWar3::RemoveEntry(int32_t playerId) {
    m_entries.erase(
        std::remove_if(m_entries.begin(), m_entries.end(),
            [playerId](const LeaderboardEntry& e) { return e.playerId == playerId; }),
        m_entries.end());
}

void CLeaderboardWar3::ClearEntries() { m_entries.clear(); }

size_t CLeaderboardWar3::GetEntryCount() const { return m_entries.size(); }

int32_t CLeaderboardWar3::GetEntryPlayerId(size_t index) const {
    return (index < m_entries.size()) ? m_entries[index].playerId : -1;
}

int32_t CLeaderboardWar3::GetEntryScore(size_t index) const {
    return (index < m_entries.size()) ? m_entries[index].score : 0;
}

bool CLeaderboardWar3::IsVisible() const { return m_visible; }
void CLeaderboardWar3::SetVisible(bool visible) { m_visible = visible; }
