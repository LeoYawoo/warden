#pragma once

#include <cstdint>
#include <string>

// Reverse engineered from Warcraft III binary
// CPlayerWar3 manages Warcraft III players

class CPlayerWar3 {
public:
    CPlayerWar3();
    ~CPlayerWar3();

    // Player properties
    int32_t GetPlayerId() const;
    void SetPlayerId(int32_t id);

    const char* GetPlayerName() const;
    void SetPlayerName(const char* name);

    // Player state
    bool IsHuman() const;
    void SetHuman(bool human);

    bool IsComputer() const;
    void SetComputer(bool computer);

    // Player resources
    int32_t GetGold() const;
    void SetGold(int32_t gold);
    void AddGold(int32_t amount);

    int32_t GetLumber() const;
    void SetLumber(int32_t lumber);
    void AddLumber(int32_t amount);

    // Player food
    int32_t GetFood() const;
    void SetFood(int32_t food);
    int32_t GetFoodCap() const;
    void SetFoodCap(int32_t foodCap);
    void AddFoodCap(int32_t amount);

    // Player state
    bool IsObserverOnly() const;
    bool IsPureObserver() const;

protected:
    int32_t m_playerId;
    std::string m_playerName;
    bool m_human;
    bool m_computer;
    int32_t m_gold;
    int32_t m_lumber;
    int32_t m_food;
    int32_t m_foodCap;
    bool m_observerOnly;
    bool m_pureObserver;
};
