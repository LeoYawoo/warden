#pragma once

#include <cstdint>
#include <string>

// Reverse engineered from Warcraft III binary
// CDestructable represents a destructable object

class CDestructable {
public:
    CDestructable();
    ~CDestructable();

    // Destructable properties
    int32_t GetDestructableId() const;
    void SetDestructableId(int32_t id);

    const char* GetDestructableName() const;
    void SetDestructableName(const char* name);

    // Destructable state
    int32_t GetHealth() const;
    void SetHealth(int32_t health);

    int32_t GetMaxHealth() const;
    void SetMaxHealth(int32_t maxHealth);

    bool IsInvulnerable() const;
    void SetInvulnerable(bool invulnerable);

    // Destructable position
    float GetX() const;
    float GetY() const;
    void SetPosition(float x, float y);

protected:
    int32_t m_destructableId;
    std::string m_destructableName;
    int32_t m_health;
    int32_t m_maxHealth;
    bool m_invulnerable;
    float m_x;
    float m_y;
};
