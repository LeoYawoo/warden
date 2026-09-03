#pragma once

#include <cstdint>

// Forward declarations
class CUnit;

// Reverse engineered from Warcraft III binary
// CCaptainAI manages captain AI behavior

class CCaptainAI {
public:
    CCaptainAI();
    ~CCaptainAI();

    // AI properties
    int32_t GetCaptainId() const;
    void SetCaptainId(int32_t id);

    // AI state
    bool IsEnabled() const;
    void SetEnabled(bool enabled);

    // AI operations
    void Update(float deltaTime);
    void Reset();

protected:
    int32_t m_captainId;
    bool m_enabled;
};
