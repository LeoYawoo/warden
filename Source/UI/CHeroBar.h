#pragma once

#include <cstdint>
#include <vector>

// Forward declarations
class CUnit;

// Reverse engineered from Warcraft III binary
// CHeroBar displays hero units

class CHeroBar {
public:
    CHeroBar();
    ~CHeroBar();

    // Hero bar operations
    void AddHero(CUnit* hero);
    void RemoveHero(CUnit* hero);
    void ClearHeroes();

    // Hero bar properties
    size_t GetHeroCount() const;
    CUnit* GetHero(size_t index) const;

    // Hero bar state
    bool IsVisible() const;
    void SetVisible(bool visible);

protected:
    std::vector<CUnit*> m_heroes;
    bool m_visible;
};
