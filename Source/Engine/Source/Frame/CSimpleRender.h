#pragma once

#include "CSimpleFrame.h"
#include <cstdint>

// Reverse engineered from Warcraft III binary
// CSimpleRender handles simple rendering

class CSimpleRender : public CSimpleFrame {
public:
    CSimpleRender();
    virtual ~CSimpleRender();

    // Render properties
    uint32_t GetColor() const;
    void SetColor(uint32_t color);

    float GetAlpha() const;
    void SetAlpha(float alpha);

    // Render operations
    virtual void Render() override;

protected:
    uint32_t m_color;
    float m_alpha;
};
