#pragma once

#include <cstdint>

// Forward declarations
class CUnit;

// Reverse engineered from Warcraft III binary
// CUnitUI manages unit UI elements

class CUnitUI {
public:
    CUnitUI();
    ~CUnitUI();

    // UI properties
    void SetUnit(CUnit* unit);
    CUnit* GetUnit() const;

    // UI state
    bool IsSelected() const;
    void SetSelected(bool selected);

    bool IsHighlighted() const;
    void SetHighlighted(bool highlighted);

    // UI visibility
    bool IsVisible() const;
    void SetVisible(bool visible);

protected:
    CUnit* m_unit;
    bool m_selected;
    bool m_highlighted;
    bool m_visible;
};
