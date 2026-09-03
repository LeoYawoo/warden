#pragma once

#include <cstdint>

// Reverse engineered from Warcraft III binary
// NIpse::CPoReal represents a proximity real value

namespace NIpse {
    class CPoReal {
    public:
        CPoReal();
        CPoReal(float value, float target);
        ~CPoReal();

        // Value operations
        float GetValue() const;
        void SetValue(float value);

        float GetTarget() const;
        void SetTarget(float target);

        // State operations
        bool HasReachedTarget() const;
        void Update(float deltaTime);

        // Comparison
        bool operator==(const CPoReal& other) const;
        bool operator!=(const CPoReal& other) const;
        bool operator<(const CPoReal& other) const;
        bool operator>(const CPoReal& other) const;

    private:
        float m_value;
        float m_target;
        float m_speed;
    };
}
