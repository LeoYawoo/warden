#include "CWidget.h"

// Reverse engineered from Warcraft III binary

CWidget::CWidget()
    : CAgentBaseAbs(),
      m_widgetId(0),
      m_widgetType(0),
      m_flags(0),
      m_x(0.0f),
      m_y(0.0f),
      m_width(0.0f),
      m_height(0.0f),
      m_owner(nullptr) {
    // Virtual table set in constructor
}

CWidget::~CWidget() {
    // Virtual destructor
}

int32_t CWidget::GetWidgetId() const {
    return m_widgetId;
}

void CWidget::SetWidgetId(int32_t id) {
    m_widgetId = id;
}

int32_t CWidget::GetWidgetType() const {
    return m_widgetType;
}

void CWidget::SetWidgetType(int32_t type) {
    m_widgetType = type;
}

bool CWidget::IsVisible() const {
    return (m_flags & 0x01) != 0;
}

void CWidget::SetVisible(bool visible) {
    if (visible) {
        m_flags |= 0x01;
    } else {
        m_flags &= ~0x01;
    }
}

bool CWidget::IsEnabled() const {
    return (m_flags & 0x02) != 0;
}

void CWidget::SetEnabled(bool enabled) {
    if (enabled) {
        m_flags |= 0x02;
    } else {
        m_flags &= ~0x02;
    }
}

float CWidget::GetX() const {
    return m_x;
}

float CWidget::GetY() const {
    return m_y;
}

void CWidget::SetPosition(float x, float y) {
    m_x = x;
    m_y = y;
}

float CWidget::GetWidth() const {
    return m_width;
}

float CWidget::GetHeight() const {
    return m_height;
}

void CWidget::SetSize(float width, float height) {
    m_width = width;
    m_height = height;
}
