#include "CScoreScreen.h"
#include <algorithm>

// Reverse engineered from Warcraft III binary

CScoreScreen::CScoreScreen() : m_initialized(false), m_visible(false) {}
CScoreScreen::~CScoreScreen() { Shutdown(); }

bool CScoreScreen::Initialize() {
    m_initialized = true;
    m_visible = true;
    return true;
}

void CScoreScreen::Shutdown() {
    m_initialized = false;
    m_scores.clear();
}

bool CScoreScreen::IsInitialized() const { return m_initialized; }

void CScoreScreen::AddPlayerScore(int32_t playerId, const char* name, int32_t score) {
    if (!name) return;
    PlayerScore ps;
    ps.playerId = playerId;
    ps.name = name;
    ps.score = score;
    m_scores.push_back(ps);
    std::sort(m_scores.begin(), m_scores.end(),
        [](const PlayerScore& a, const PlayerScore& b) { return a.score > b.score; });
}

void CScoreScreen::ClearScores() { m_scores.clear(); }

size_t CScoreScreen::GetPlayerCount() const { return m_scores.size(); }

const char* CScoreScreen::GetPlayerName(size_t index) const {
    return (index < m_scores.size()) ? m_scores[index].name.c_str() : nullptr;
}

int32_t CScoreScreen::GetPlayerScore(size_t index) const {
    return (index < m_scores.size()) ? m_scores[index].score : 0;
}

bool CScoreScreen::IsVisible() const { return m_visible; }
void CScoreScreen::SetVisible(bool visible) { m_visible = visible; }
