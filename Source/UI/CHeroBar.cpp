#include "CHeroBar.h"
#include <algorithm>

// Reverse engineered from Warcraft III binary

CHeroBar::CHeroBar() : m_visible(true) {}
CHeroBar::~CHeroBar() {}

void CHeroBar::AddHero(CUnit* hero) {
    if (hero) m_heroes.push_back(hero);
}

void CHeroBar::RemoveHero(CUnit* hero) {
    auto it = std::find(m_heroes.begin(), m_heroes.end(), hero);
    if (it != m_heroes.end()) {
        m_heroes.erase(it);
    }
}

void CHeroBar::ClearHeroes() { m_heroes.clear(); }

size_t CHeroBar::GetHeroCount() const { return m_heroes.size(); }

CUnit* CHeroBar::GetHero(size_t index) const {
    return (index < m_heroes.size()) ? m_heroes[index] : nullptr;
}

bool CHeroBar::IsVisible() const { return m_visible; }
void CHeroBar::SetVisible(bool visible) { m_visible = visible; }
