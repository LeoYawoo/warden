#include "CPoReal.h"
#include <cmath>

// Reverse engineered from Warcraft III binary

namespace NIpse {

CPoReal::CPoReal() : m_value(0.0f), m_target(0.0f), m_speed(1.0f) {}

CPoReal::CPoReal(float value, float target) : m_value(value), m_target(target), m_speed(1.0f) {}

CPoReal::~CPoReal() {}

float CPoReal::GetValue() const { return m_value; }
void CPoReal::SetValue(float value) { m_value = value; }

float CPoReal::GetTarget() const { return m_target; }
void CPoReal::SetTarget(float target) { m_target = target; }

bool CPoReal::HasReachedTarget() const {
    return std::abs(m_value - m_target) < 0.001f;
}

void CPoReal::Update(float deltaTime) {
    if (!HasReachedTarget()) {
        float diff = m_target - m_value;
        float step = m_speed * deltaTime;
        if (std::abs(diff) <= step) {
            m_value = m_target;
        } else {
            m_value += (diff > 0 ? step : -step);
        }
    }
}

bool CPoReal::operator==(const CPoReal& other) const { return m_value == other.m_value; }
bool CPoReal::operator!=(const CPoReal& other) const { return m_value != other.m_value; }
bool CPoReal::operator<(const CPoReal& other) const { return m_value < other.m_value; }
bool CPoReal::operator>(const CPoReal& other) const { return m_value > other.m_value; }

} // namespace NIpse
