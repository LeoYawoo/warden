#pragma once

#include "Engine/Source/Agile/CAgent.h"

// Forward declarations
class CUnit;

// Reverse engineered from Warcraft III binary
// CWidget is a base class for UI widgets

class CWidget : public CAgentBaseAbs {
public:
    CWidget();
    virtual ~CWidget();

    // Widget properties
    int32_t GetWidgetId() const;
    void SetWidgetId(int32_t id);

    int32_t GetWidgetType() const;
    void SetWidgetType(int32_t type);

    // Widget state
    bool IsVisible() const;
    void SetVisible(bool visible);

    bool IsEnabled() const;
    void SetEnabled(bool enabled);

    // Widget position
    float GetX() const;
    float GetY() const;
    void SetPosition(float x, float y);

    // Widget size
    float GetWidth() const;
    float GetHeight() const;
    void SetSize(float width, float height);

protected:
    // Widget data
    int32_t m_widgetId;     // offset +84
    int32_t m_widgetType;   // offset +88
    int32_t m_flags;        // offset +92
    float m_x;              // offset +96
    float m_y;              // offset +100
    float m_width;          // offset +104
    float m_height;         // offset +108
    CUnit* m_owner;         // offset +112
};
