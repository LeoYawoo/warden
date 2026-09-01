#pragma once

#include "CAgentField.h"
#include "Tempest/C3Vector.h"

// Reverse engineered from Warcraft III binary
// Address: 0x77BF93
// ProjectilePosition tracks projectile position with velocity

class ProjectilePosition : public CAgentField {
public:
    ProjectilePosition();
    virtual ~ProjectilePosition();

    // Set projectile position
    void Set(const Tempest::C3Vector& position);

    // Get current position
    const Tempest::C3Vector& GetPosition() const;

    // Get velocity
    const Tempest::C3Vector& GetVelocity() const;

    // Set velocity
    void SetVelocity(const Tempest::C3Vector& velocity);

    // Update position based on velocity and time
    void Update(float deltaTime);

    // Check if projectile has reached target
    bool HasReachedTarget() const;

    // Set target position
    void SetTarget(const Tempest::C3Vector& target);

private:
    Tempest::C3Vector m_position;
    Tempest::C3Vector m_velocity;
    Tempest::C3Vector m_target;
    float m_speed;
    bool m_hasTarget;
};
