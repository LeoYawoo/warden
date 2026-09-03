#include "CPlayerWar3.h"

// Reverse engineered from Warcraft III binary

CPlayerWar3::CPlayerWar3()
    : m_playerId(0), m_human(true), m_computer(false),
      m_gold(0), m_lumber(0), m_food(0), m_foodCap(10),
      m_observerOnly(false), m_pureObserver(false) {
}

CPlayerWar3::~CPlayerWar3() {}

int32_t CPlayerWar3::GetPlayerId() const { return m_playerId; }
void CPlayerWar3::SetPlayerId(int32_t id) { m_playerId = id; }

const char* CPlayerWar3::GetPlayerName() const { return m_playerName.c_str(); }
void CPlayerWar3::SetPlayerName(const char* name) { m_playerName = name ? name : ""; }

bool CPlayerWar3::IsHuman() const { return m_human; }
void CPlayerWar3::SetHuman(bool human) { m_human = human; }

bool CPlayerWar3::IsComputer() const { return m_computer; }
void CPlayerWar3::SetComputer(bool computer) { m_computer = computer; }

int32_t CPlayerWar3::GetGold() const { return m_gold; }
void CPlayerWar3::SetGold(int32_t gold) { m_gold = gold; }
void CPlayerWar3::AddGold(int32_t amount) { m_gold += amount; }

int32_t CPlayerWar3::GetLumber() const { return m_lumber; }
void CPlayerWar3::SetLumber(int32_t lumber) { m_lumber = lumber; }
void CPlayerWar3::AddLumber(int32_t amount) { m_lumber += amount; }

int32_t CPlayerWar3::GetFood() const { return m_food; }
void CPlayerWar3::SetFood(int32_t food) { m_food = food; }
int32_t CPlayerWar3::GetFoodCap() const { return m_foodCap; }
void CPlayerWar3::SetFoodCap(int32_t foodCap) { m_foodCap = foodCap; }
void CPlayerWar3::AddFoodCap(int32_t amount) { m_foodCap += amount; }

bool CPlayerWar3::IsObserverOnly() const { return m_observerOnly; }
bool CPlayerWar3::IsPureObserver() const { return m_pureObserver; }
