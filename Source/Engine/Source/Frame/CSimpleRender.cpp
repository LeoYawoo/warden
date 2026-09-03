#include "CSimpleRender.h"

// Reverse engineered from Warcraft III binary

CSimpleRender::CSimpleRender() : m_color(0xFFFFFFFF), m_alpha(1.0f) {}
CSimpleRender::~CSimpleRender() {}

uint32_t CSimpleRender::GetColor() const { return m_color; }
void CSimpleRender::SetColor(uint32_t color) { m_color = color; }

float CSimpleRender::GetAlpha() const { return m_alpha; }
void CSimpleRender::SetAlpha(float alpha) { m_alpha = alpha; }

void CSimpleRender::Render() {
    // TODO: Implement actual rendering
}
