#pragma once

#include "CControl.h"
#include <cstdint>

// Reverse engineered from Warcraft III binary
// CScrollBar is a scroll bar UI control

class CScrollBar : public CControl {
public:
    CScrollBar();
    virtual ~CScrollBar();

    // ScrollBar properties
    float GetScrollPosition() const;
    void SetScrollPosition(float position);

    float GetScrollRange() const;
    void SetScrollRange(float range);

    float GetPageSize() const;
    void SetPageSize(float pageSize);

    // ScrollBar operations
    void ScrollUp(float amount);
    void ScrollDown(float amount);

    // ScrollBar state
    bool IsVertical() const;
    void SetVertical(bool vertical);

protected:
    float m_scrollPosition;
    float m_scrollRange;
    float m_pageSize;
    bool m_vertical;
};
