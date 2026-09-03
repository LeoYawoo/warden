#include "CSimpleRender.h"

// Reverse engineered from Warcraft III binary

CSimpleRender::CSimpleRender() : m_color(0xFFFFFFFF), m_alpha(1.0f) {}
CSimpleRender::~CSimpleRender() {}

uint32_t CSimpleRender::GetColor() const { return m_color; }
void CSimpleRender::SetColor(uint32_t color) { m_color = color; }

float CSimpleRender::GetAlpha() const { return m_alpha; }
void CSimpleRender::SetAlpha(float alpha) { m_alpha = alpha; }

void CSimpleRender::Render() {
    // Render the simple render frame
    // In a real implementation, this would use the graphics API to render
    // a colored rectangle with the specified color and alpha
    if (!m_enabled) return;

    // Placeholder for actual rendering code
    // Would call GxDraw or similar graphics functions
}
