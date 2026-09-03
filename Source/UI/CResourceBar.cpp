#include "CResourceBar.h"

// Reverse engineered from Warcraft III binary

CResourceBar::CResourceBar()
    : m_gold(0), m_lumber(0), m_food(0), m_foodCap(10), m_visible(true) {
}

CResourceBar::~CResourceBar() {}

int32_t CResourceBar::GetGold() const { return m_gold; }
void CResourceBar::SetGold(int32_t gold) { m_gold = gold; }

int32_t CResourceBar::GetLumber() const { return m_lumber; }
void CResourceBar::SetLumber(int32_t lumber) { m_lumber = lumber; }

int32_t CResourceBar::GetFood() const { return m_food; }
int32_t CResourceBar::GetFoodCap() const { return m_foodCap; }

void CResourceBar::SetFood(int32_t food, int32_t foodCap) {
    m_food = food;
    m_foodCap = foodCap;
}

bool CResourceBar::IsVisible() const { return m_visible; }
void CResourceBar::SetVisible(bool visible) { m_visible = visible; }
