#pragma once

#include <cstdint>

namespace NIpse {
    class CPoReal {
    public:
        // Member variables
        float m_value = 0.0f;
        float m_target = 0.0f;
        float m_velocity = 0.0f;
        float m_min = 0.0f;
        float m_max = 1.0f;
        bool m_active = false;

        // Constructor
        CPoReal() = default;

        CPoReal(float value, float target = 0.0f)
            : m_value(value), m_target(target), m_velocity(0.0f),
              m_min(0.0f), m_max(1.0f), m_active(false) {}

        // Getters
        float GetValue() const { return m_value; }
        float GetTarget() const { return m_target; }
        float GetVelocity() const { return m_velocity; }
        float GetMin() const { return m_min; }
        float GetMax() const { return m_max; }
        bool IsActive() const { return m_active; }

        // Setters
        void SetValue(float value) { m_value = value; }
        void SetTarget(float target) { m_target = target; }
        void SetVelocity(float velocity) { m_velocity = velocity; }
        void SetRange(float min, float max) { m_min = min; m_max = max; }
        void SetActive(bool active) { m_active = active; }

        // Update value towards target
        void Update(float deltaTime) {
            if (!m_active) return;

            float diff = m_target - m_value;
            if (std::abs(diff) < 0.0001f) {
                m_value = m_target;
                m_velocity = 0.0f;
            } else {
                m_value += m_velocity * deltaTime;
                m_value = std::max(m_min, std::min(m_max, m_value));
            }
        }

        // Check if value has reached target
        bool HasReachedTarget() const {
            return std::abs(m_value - m_target) < 0.0001f;
        }

        // Reset to initial state
        void Reset(float value = 0.0f) {
            m_value = value;
            m_target = value;
            m_velocity = 0.0f;
            m_active = false;
        }
    };
}



