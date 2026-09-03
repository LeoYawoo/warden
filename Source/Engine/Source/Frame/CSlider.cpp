#include "CSlider.h"
#include <algorithm>

// Reverse engineered from Warcraft III binary

CSlider::CSlider() : m_value(0), m_minValue(0), m_maxValue(100), m_step(1) {
    m_controlType = "Slider";
}

CSlider::~CSlider() {}

float CSlider::GetValue() const { return m_value; }
void CSlider::SetValue(float value) { m_value = std::max(m_minValue, std::min(value, m_maxValue)); }

float CSlider::GetMinValue() const { return m_minValue; }
void CSlider::SetMinValue(float minValue) { m_minValue = minValue; }

float CSlider::GetMaxValue() const { return m_maxValue; }
void CSlider::SetMaxValue(float maxValue) { m_maxValue = maxValue; }

float CSlider::GetStep() const { return m_step; }
void CSlider::SetStep(float step) { m_step = step; }

void CSlider::StepUp() { SetValue(m_value + m_step); }
void CSlider::StepDown() { SetValue(m_value - m_step); }
