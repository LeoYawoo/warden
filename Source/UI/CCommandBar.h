#pragma once

#include <cstdint>
#include <vector>

// Forward declarations
class CUnit;

// Reverse engineered from Warcraft III binary
// CCommandBar displays unit commands

class CCommandBar {
public:
    CCommandBar();
    ~CCommandBar();

    // Command bar properties
    void SetSelectedUnit(CUnit* unit);
    CUnit* GetSelectedUnit() const;

    // Command bar state
    bool IsVisible() const;
    void SetVisible(bool visible);

    // Command bar commands
    size_t GetCommandCount() const;
    const char* GetCommandName(size_t index) const;
    int32_t GetCommandId(size_t index) const;

protected:
    CUnit* m_selectedUnit;
    bool m_visible;
};
