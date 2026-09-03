#pragma once

#include <cstdint>

// Forward declarations
class CUnit;

// Reverse engineered from Warcraft III binary
// CPortraitButton displays unit portrait

class CPortraitButton {
public:
    CPortraitButton();
    ~CPortraitButton();

    // Portrait properties
    void SetUnit(CUnit* unit);
    CUnit* GetUnit() const;

    // Portrait state
    bool IsVisible() const;
    void SetVisible(bool visible);

    // Portrait animation
    bool IsPlaying() const;
    void SetPlaying(bool playing);

protected:
    CUnit* m_unit;
    bool m_visible;
    bool m_playing;
};
