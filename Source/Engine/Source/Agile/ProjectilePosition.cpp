#include "ProjectilePosition.h"

// Reverse engineered from Warcraft III binary
// Address: 0x77BF93

ProjectilePosition::ProjectilePosition() : CAgentField(), m_speed(0.0f), m_hasTarget(false) {
    // Virtual table set in constructor
}

ProjectilePosition::~ProjectilePosition() {
    // Virtual destructor
}

void ProjectilePosition::Set(const Tempest::C3Vector& position) {
    m_position = position;
}

const Tempest::C3Vector& ProjectilePosition::GetPosition() const {
    return m_position;
}

const Tempest::C3Vector& ProjectilePosition::GetVelocity() const {
    return m_velocity;
}

void ProjectilePosition::SetVelocity(const Tempest::C3Vector& velocity) {
    m_velocity = velocity;
}

void ProjectilePosition::Update(float deltaTime) {
    if (m_hasTarget) {
        // Calculate direction to target
        Tempest::C3Vector direction = m_target - m_position;
        float distance = direction.Mag();

        if (distance > 0.001f) {
            // Normalize and apply speed
            direction = direction * (m_speed / distance);
            m_velocity = direction;
        }
    }

    // Update position
    m_position = m_position + m_velocity * deltaTime;
}

bool ProjectilePosition::HasReachedTarget() const {
    if (!m_hasTarget) {
        return false;
    }

    Tempest::C3Vector direction = m_target - m_position;
    float distance = direction.Mag();
    return distance < 0.1f;
}

void ProjectilePosition::SetTarget(const Tempest::C3Vector& target) {
    m_target = target;
    m_hasTarget = true;
}
