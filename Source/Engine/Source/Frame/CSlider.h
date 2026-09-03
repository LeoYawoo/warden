#pragma once

#include "CControl.h"
#include <cstdint>

// Reverse engineered from Warcraft III binary
// CSlider is a slider UI control

class CSlider : public CControl {
public:
    CSlider();
    virtual ~CSlider();

    // Slider properties
    float GetValue() const;
    void SetValue(float value);

    float GetMinValue() const;
    void SetMinValue(float minValue);

    float GetMaxValue() const;
    void SetMaxValue(float maxValue);

    float GetStep() const;
    void SetStep(float step);

    // Slider operations
    void StepUp();
    void StepDown();

protected:
    float m_value;
    float m_minValue;
    float m_maxValue;
    float m_step;
};
