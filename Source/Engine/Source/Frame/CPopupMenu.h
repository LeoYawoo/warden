#pragma once

#include "CMenu.h"
#include <cstdint>

// Reverse engineered from Warcraft III binary
// CPopupMenu is a popup menu UI control

class CPopupMenu : public CMenu {
public:
    CPopupMenu();
    virtual ~CPopupMenu();

    // PopupMenu properties
    float GetPopupX() const;
    float GetPopupY() const;
    void SetPopupPosition(float x, float y);

    // PopupMenu operations
    void Show(float x, float y);
    void Hide();

protected:
    float m_popupX;
    float m_popupY;
};
