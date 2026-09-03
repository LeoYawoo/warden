#pragma once

#include <cstdint>

// Reverse engineered from Warcraft III binary
// CResourceBar displays player resources

class CResourceBar {
public:
    CResourceBar();
    ~CResourceBar();

    // Resource properties
    int32_t GetGold() const;
    void SetGold(int32_t gold);

    int32_t GetLumber() const;
    void SetLumber(int32_t lumber);

    int32_t GetFood() const;
    int32_t GetFoodCap() const;
    void SetFood(int32_t food, int32_t foodCap);

    // Resource bar state
    bool IsVisible() const;
    void SetVisible(bool visible);

protected:
    int32_t m_gold;
    int32_t m_lumber;
    int32_t m_food;
    int32_t m_foodCap;
    bool m_visible;
};
